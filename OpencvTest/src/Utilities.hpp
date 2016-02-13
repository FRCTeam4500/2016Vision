/*
 * Utilities.h
 *
 *  Created on: Jan 23, 2016
 *      Author: aditya
 */

#ifndef SRC_UTILITIES_HPP_
#define SRC_UTILITIES_HPP_
#ifndef _INCLUDE_CORE_HPP
#define _INCLUDE_CORE_HPP
#include <opencv2/core/core.hpp>
#endif

#ifndef _INCLUDE_HIGHGUI_HPP
#define _INCLUDE_HIGHGUI_HPP
#include <opencv2/highgui/highgui.hpp>
#endif

#ifndef _INCLUDE_OPENCV_HPP
#define _INCLUDE_OPENCV_HPP
#include <opencv2/opencv.hpp>
#endif

#ifndef _INCLUDE_STRING
#define _INCLUDE_STRING
#include <string>
#endif

#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H
#include <stdlib.h>
#endif

#ifndef _INCLUDE_ALGORITHM
#define _INCLUDE_ALGORITHM
#include <algorithm>
#endif

#define KERNEL_SIZE 15
#define WIDTH_FOV 60
#define HEIGHT_FOV 45
#define TAN_HALF_WIDTH_FOV .577
#define TAN_HALF_HEIGHT_FOV .414
#define WIDTH ((double)640)
#define HEIGHT ((double)480)
//0,211,143,257,0,210
#define RMIN 0
#define RMAX 211
#define GMIN 143
#define GMAX 256
#define BMIN 0
#define BMAX 210

struct Contour{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
};

struct ImageReport{
	cv::Point2d center;
	cv::Point2d angles;
	bool goalIsPresent;
	Contour bestContour;
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
Contour secondDerivative(Contour c);
Contour derivative(Contour c);
cv::Point2d getCenter(std::vector<cv::Point> contour);
cv::Point2d getAnglesFromCenter(cv::Point2d center);
ImageReport getImageReport(cv::Mat image);


int properModulus(int i, int j);

#endif /* SRC_UTILITIES_HPP_ */
