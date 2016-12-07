/*
 * qrscan.h
 *
 *  Created on: Dec 4, 2016
 *      Author: opencv
 */
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
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
#include "qrdecode.h"
int textlearn();
int testproc();

