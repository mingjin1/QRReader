/*
 * qrdecode.h
 *
 *  Created on: Dec 4, 2016
 *      Author: opencv
 */
#ifndef QR_ERROR
#define QR_ERROR "No QR code detected! \n"
#endif
#ifndef SRC_QRDECODE_H_
#define SRC_QRDECODE_H_
namespace qrdecode{
	std::string decodeQR(cv::Mat qr_gray);
}
#endif /* SRC_QRDECODE_H_ */
