/*
 * Utilities.h
 *
 *  Created on: Jan 23, 2016
 *      Author: aditya
 */

#ifndef SRC_UTILITIES_HPP_
#define SRC_UTILITIES_HPP_
#ifndef _CORE_HPP
#define _CORE_HPP
#include <opencv2/core/core.hpp>
#endif

#ifndef _HIGHGUI_HPP
#define _HIGHGUI_HPP
#include <opencv2/highgui/highgui.hpp>
#endif

#ifndef _OPENCV_HPP
#define _OPENCV_HPP
#include <opencv2/opencv.hpp>
#endif

#ifndef _STRING
#define _STRING
#include <string>
#endif

#ifndef _STDLIB
#define _STDLIB
#include <stdlib.h>
#endif

#ifndef _ALGORITHM
#define _ALGORITHM
#include <algorithm>
#endif

#define KERNEL_SIZE 15

struct Contour{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
};


cv::Mat getFieldImage(int n);
cv::Mat multipleThresholdRGB(cv::Mat image, int rlow, int rhigh, int glow, int ghigh, int blow, int bhigh);
cv::Mat multipleThresholdHSV(cv::Mat image, int hlow, int hhigh, int slow, int shigh, int vlow, int vhigh);
void singleThreshold(cv::Mat image, cv::Mat dest, int low, int high);
Contour findContoursFromBinary(cv::Mat binaryImage);
void drawContourList(cv::Mat canvas, Contour contours);
Contour filterContours(Contour contours, double minArea, int minPerimeter, int minWidth, int maxWidth, int minHeight, int maxHeight, double minSolidity, double maxSolidity);
void saveImage(int n, cv::Mat image, cv::Mat binary);
cv::Mat floodFill(cv::Mat binaryImage);
void removeHoles(cv::Mat image);
cv::Mat combineTwoImages(cv::Mat img1, cv::Mat img2);
Contour approximateToPolygon(Contour contour);
Contour removeBumps(Contour contours);
void drawContourPoints(cv::Mat img, Contour contours);
void saveImage(int n, cv::Mat image, cv::Mat binary, bool shouldConvert);
std::vector<cv::Point> pickBestContour(Contour contours);
void saveImage(int n, cv::Mat image);
Contour findCornersFromContour(Contour contours);
double* convolution1D(double* src, int length, double* kernel, int kernelSize);
double* getConvolutionKernel(int length);

#endif /* SRC_UTILITIES_HPP_ */
