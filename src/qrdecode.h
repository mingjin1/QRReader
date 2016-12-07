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
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/MultiFormatReader.h>
#include "zxing/MatSource.h"
#endif /* SRC_QRDECODE_H_ */
