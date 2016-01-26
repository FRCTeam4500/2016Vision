/*
 * Utilities.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: aditya
 */

#include "Utilities.hpp"
using namespace cv;
Mat getFieldImage(int n){

	 Mat image = imread((cv::String)("./RealFullField/" + std::to_string(n) + ".jpg"), 1);
	 return image;

}

Mat multipleThreshold(Mat image, int rlow, int rhigh, int glow, int ghigh, int blow, int bhigh){
	/**
	 * Assumes that the image is in BGR
	 */

	Mat channels[3];
	split(image, channels);

	singleThreshold(channels[0], channels[0], blow, bhigh);
	singleThreshold(channels[1], channels[1], glow, ghigh);
	singleThreshold(channels[2], channels[2], rlow, rhigh);

	Mat tmp;
	bitwise_and(channels[0], channels[1], tmp);
	bitwise_and(channels[2], tmp, tmp);
	return tmp;


}

void singleThreshold(Mat image, Mat dest, int low, int high){
	Mat upperHalf;
	Mat lowerHalf;

	threshold(image, upperHalf, low, 255, THRESH_BINARY);
	threshold(image, lowerHalf, high, 255, THRESH_BINARY_INV);
	bitwise_and(upperHalf, lowerHalf, dest);

}

Mat floodFill(Mat binaryImage){
	// Floodfill from point (0, 0)
	Mat im_floodfill = binaryImage.clone();
	floodFill(im_floodfill, cv::Point(0,0), Scalar(255));

	// Invert floodfilled image
	Mat im_floodfill_inv;
	bitwise_not(im_floodfill, im_floodfill_inv);

	// Combine the two images to get the foreground.
	Mat im_out = (binaryImage | im_floodfill_inv);

	return im_out;
}



Contour findContoursFromBinary(Mat binaryImage){
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(binaryImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1);



	Contour ret;
	ret.contours = contours;
	ret.hierarchy = hierarchy;

	return ret;


}

void drawContourList(Contour contours, Mat canvas){
	for(unsigned int i = 0; i < contours.contours.size(); i++){
			Scalar color = Scalar(0, 0, 255);
			drawContours(canvas, contours.contours, i, color, 1, 8, contours.hierarchy, 0, Point());
		}
}

Contour filterContours(Contour contours, double minArea, int minPerimeter, int minWidth, int maxWidth, int minHeight, int maxHeight, double solidity){
	Contour acceptableContours;
	//acceptableContours.contours = new std::vector<std::vector<Point>>();
	//acceptableContours.hierarchy = new std::vector<Vec4i>();


	for(int i = 0; i < contours.contours.size(); i++){
		if(contourArea(contours.contours[i]) >= minArea && arcLength(contours.contours[i], false) >= minPerimeter){
			Rect bounding = boundingRect(contours.contours[i]);
			if(bounding.width >= minWidth && bounding.height >= minHeight && bounding.width <= maxWidth && bounding.height <= maxHeight){
				std::vector<Point> hull;
				convexHull(contours.contours[i], hull);

				double hullArea = contourArea(hull);
				double ratio = contourArea(contours.contours[i]) / hullArea;
				if(hullArea != 0 && ratio <= solidity){
					acceptableContours.contours.push_back(contours.contours[i]);
					acceptableContours.hierarchy.push_back(contours.hierarchy[i]);
				}
			}

		}
	}

	return acceptableContours;


}

void saveImage(int n, Mat image, Mat binary){
	Mat RGB_binary;
	cvtColor(binary, RGB_binary, CV_GRAY2BGR,3);

	Mat tmp = combineTwoImages(image, RGB_binary);

	imwrite((cv::String)("./AnalyzedImages/" + std::to_string(n) + ".jpg"), tmp);
}

void removeHoles(Mat image){
	//Mat kernel = Mat::ones(3, 3, CV_8U);
	//dilate(image, image, kernel, Point(-1, -1), 1);
	//erode(image, image, kernel, Point(-1, -1), 1);

	Mat kernel = Mat::ones(3, 1, CV_8UC1);
	dilate(image, image, kernel, Point(-1, -1), 3);
	erode(image, image, kernel, Point(-1, -1), 3);

	kernel = Mat::ones(1, 3, CV_8UC1);
	dilate(image, image, kernel, Point(-1, -1), 3);
	erode(image, image, kernel, Point(-1, -1), 3);
}

Mat combineTwoImages(Mat img1, Mat img2){
	Size sz1 = img1.size();
	Size sz2 = img2.size();

	Mat img3(sz1.height, sz1.width*2, CV_8UC3);
	Mat left(img3, Rect(0, 0, sz1.width, sz1.height));
	img1.copyTo(left);
	Mat right(img3, Rect(sz1.width, 0, sz2.width, sz1.height));
	img2.copyTo(right);

	return img3;
}
