/*
 * textproc.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: opencv
 */
#include "qrscan.h"

using namespace std;
using namespace cv;
using namespace cv::text;

const int MIN_CONTOUR_AREA = 100;

const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

using namespace cv;
using namespace std;

int textlearn() {
	Mat imgTrainingNumbers, imgGrayscale, imgBlurred, imgThresh, imgThreshCopy;
	vector< vector<Point> > ptContours;
	vector<Vec4i> v4iHierarchy;

	Mat matClassificationInts;
	Mat matTrainingImagesAsFlattenedFloats;

	std::vector<int> intValidChars = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	                                       'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	                                       'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	                                       'U', 'V', 'W', 'X', 'Y', 'Z' };
	// possible chars we are interested in are digits 0 through 9 and capital letters A through Z, put these in vector intValidChars

	imgTrainingNumbers = cv::imread("../data/training_chars.png");

	if (imgTrainingNumbers.empty()) {
		cout << "error: image not read from file\n\n";
		return (0);
	}
	cvtColor(imgTrainingNumbers, imgGrayscale, CV_BGR2GRAY);

	GaussianBlur(imgGrayscale, imgBlurred, Size(5, 5), 0);

	adaptiveThreshold(imgBlurred, imgThresh, 255, ADAPTIVE_THRESH_GAUSSIAN_C,
			THRESH_BINARY_INV, 11, 2);

	imshow("imgThresh", imgThresh);

	imgThreshCopy = imgThresh.clone();

	findContours(imgThreshCopy, ptContours, v4iHierarchy, RETR_EXTERNAL,
			CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < ptContours.size(); i++) {
		if (contourArea(ptContours[i]) > MIN_CONTOUR_AREA) {
			Rect boundingBox = boundingRect(ptContours[i]);

			rectangle(imgTrainingNumbers, boundingBox, Scalar(0, 0, 255), 2);
			// red bounding box around contour

			Mat matROI = imgThresh(boundingBox);

			Mat matROIResized;

			resize(matROI, matROIResized,
					Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));

			imshow("matROI", matROI);
			imshow("matROIResized", matROIResized);
			imshow("imgTrainingNumbers", imgTrainingNumbers);

			int intChar = cv::waitKey(0);

			if (intChar == 27) {
				return 0; //if esc, quit program
			}else if (std::find(intValidChars.begin(), intValidChars.end(), intChar) != intValidChars.end()) {     // else if the char is in the list of chars we are looking for . . .

				matClassificationInts.push_back(intChar); // append char to list of chars

				Mat matImageFloat;
				matROIResized.convertTo(matImageFloat, CV_32FC1); // convert Mat to float

				Mat matImageFlattenedFloat = matImageFloat.reshape(1, 1); //flatten

				matTrainingImagesAsFlattenedFloats.push_back(
						matImageFlattenedFloat); // add to Mat as though it was a vector, this is necessary due to the
												 // data types that KNearest.train accepts

			}

		}
	}
	cout << "training complete\n\n";

	// save classifications to file ///////////////////////////////////////////////////////

	cv::FileStorage fsClassifications("classifications.xml",
			cv::FileStorage::WRITE);           // open the classifications file

	if (fsClassifications.isOpened() == false) { // if the file was not opened successfully
		std::cout
				<< "error, unable to open training classifications file, exiting program\n\n"; // show error message
		return (0);                                          // and exit program
	}

	fsClassifications << "classifications" << matClassificationInts; // write classifications into classifications section of classifications file
	fsClassifications.release();               // close the classifications file

	// save training images to file ///////////////////////////////////////////////////////

	cv::FileStorage fsTrainingImages("images.xml", cv::FileStorage::WRITE); // open the training images file

	if (fsTrainingImages.isOpened() == false) { // if the file was not opened successfully
		std::cout
				<< "error, unable to open training images file, exiting program\n\n"; // show error message
		return (0);                                          // and exit program
	}

	fsTrainingImages << "images" << matTrainingImagesAsFlattenedFloats; // write training images into images section of images file
	fsTrainingImages.release();                // close the training images file

	return (0);
}
