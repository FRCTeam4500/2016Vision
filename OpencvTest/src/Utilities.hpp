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

struct Contour{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
};


cv::Mat getFieldImage(int n);
cv::Mat multipleThreshold(cv::Mat image, int rlow, int rhigh, int glow, int ghigh, int blow, int bhigh);
void singleThreshold(cv::Mat image, cv::Mat dest, int low, int high);
Contour findContoursFromBinary(cv::Mat binaryImage);
void drawContourList(Contour contours, cv::Mat canvas);
Contour filterContours(Contour contours, double minArea, int minPerimeter, int minWidth, int maxWidth, int minHeight, int maxHeight, double solidity);
void saveImage(int n, cv::Mat image, cv::Mat binary);
cv::Mat floodFill(cv::Mat binaryImage);
void removeHoles(cv::Mat image);
cv::Mat combineTwoImages(cv::Mat img1, cv::Mat img2);


#endif /* SRC_UTILITIES_HPP_ */
