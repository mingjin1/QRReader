/*
 * qrdecode.cpp
 *
 *  Created on: Dec 4, 2016
 *      Author: opencv
 */


#include "qrscan.h"

using namespace cv;
using namespace std;
using namespace zxing::qrcode;
using namespace zxing;

namespace qrdecode{
	string decodeQR(Mat qr_gray){
		try{
			Ref<Reader> reader;
			reader.reset(new QRCodeReader);
			Ref<LuminanceSource> lSource = MatSource::create(qr_gray);
			Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(lSource));
			Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
			Ref<Result> result(reader->decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));
			return (result->getText()->getText());
		}catch (const ReaderException& e) {
			cerr << e.what() << " (ignoring)" << endl;
			return QR_ERROR;
		} catch (const zxing::IllegalArgumentException& e) {
			cerr << e.what() << " (ignoring)" << endl;
			return QR_ERROR;
		} catch (const zxing::Exception& e) {
			cerr << e.what() << " (ignoring)" << endl;
			return QR_ERROR;
		} catch (const std::exception& e) {
			cerr << e.what() << " (ignoring)" << endl;
			return QR_ERROR;
		}
	}
}


