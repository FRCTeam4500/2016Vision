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

	findContours(binaryImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1);//_TC89_KCOS);



	Contour ret;
	ret.contours = contours;
	ret.hierarchy = hierarchy;

	return ret;


}

void drawContourList(Mat canvas, Contour contours){
	for(unsigned int i = 0; i < contours.contours.size(); i++){
			Scalar color = Scalar(0, 0, 255);
			drawContours(canvas, contours.contours, i, color, 1, 8, contours.hierarchy, 0, Point());
		}
}

Contour filterContours(Contour contours, double minArea, int minPerimeter, int minWidth, int maxWidth, int minHeight, int maxHeight, double minSolidity, double maxSolidity){
	Contour acceptableContours;


	for(int i = 0; i < contours.contours.size(); i++){
		if(contourArea(contours.contours[i]) >= minArea && arcLength(contours.contours[i], false) >= minPerimeter){
			Rect bounding = boundingRect(contours.contours[i]);
			if(bounding.width >= minWidth && bounding.height >= minHeight && bounding.width <= maxWidth && bounding.height <= maxHeight){
				std::vector<Point> hull;
				convexHull(contours.contours[i], hull);

				double hullArea = contourArea(hull);
				double ratio = contourArea(contours.contours[i]) / hullArea;
				if(hullArea != 0 && ratio >= minSolidity && ratio <= maxSolidity){
					acceptableContours.contours.push_back(contours.contours[i]);
					acceptableContours.hierarchy.push_back(contours.hierarchy[i]);
				}
			}

		}


	}



	return acceptableContours;


}

void saveImage(int n, Mat image){
	imwrite((cv::String)("./AnalyzedImages/" + std::to_string(n) + ".jpg"), image);
}

void saveImage(int n, Mat image, Mat binary){
	Mat RGB_binary;
	cvtColor(binary, RGB_binary, CV_GRAY2BGR,3);

	Mat tmp = combineTwoImages(image, RGB_binary);

	imwrite((cv::String)("./AnalyzedImages/" + std::to_string(n) + ".jpg"), tmp);
}

void saveImage(int n, Mat image, Mat binary, bool shouldConvert){
	Mat RGB_binary;
	if(shouldConvert){
		cvtColor(binary, RGB_binary, CV_GRAY2BGR,3);
	}else{
		RGB_binary = binary;
	}

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

Contour approximateToPolygon(Contour contour){
	Contour polygons;
	polygons.hierarchy = contour.hierarchy;

	for(int i = 0; i < contour.contours.size(); i++){
		std::vector<Point> polygon;
		approxPolyDP(contour.contours[i], polygon, 4.0, true);
		polygons.contours.push_back(polygon);
	}
	return polygons;
}


//Contour removeBumps(Contour contours, double maximumNeighborRatio){
	/*Contour straightened_contours;
	straightened_contours.hierarchy = contours.hierarchy;
	for(int i = 0; i < contours.contours.size(); i++){
		double perimeter = arcLength(contours.contours[i], false);
		double perimeter_per_point = perimeter / 8;
		double* distances = new double[(unsigned int)(contours.contours[i].size()-1)];

		for(int j = 0; j < contours.contours[i].size() - 1; j++){
			distances[j] = norm(contours.contours[i][j] - contours.contours[i][j+1]);
		}

		std::vector<Point> straightened_contour;

				//edge case for first point - will just ignore last point and add the first point again at the end
		if(distances[0] >= maximumNeighborRatio * perimeter_per_point || distances[contours.contours[i].size()-1] >= maximumNeighborRatio * perimeter_per_point){
			straightened_contour.push_back(contours.contours[i][0]);
		}

		for(int j = 1; j<contours.contours[i].size()-1; j++){
			if(distances[j-1] >= maximumNeighborRatio * perimeter_per_point || distances[j] >= maximumNeighborRatio * perimeter_per_point){
				straightened_contour.push_back(contours.contours[i][j]);
			}
		}



		straightened_contour.push_back(straightened_contour.front()); //closes the contour
		straightened_contours.contours.push_back(straightened_contour);
		delete[] distances;
	}

	return straightened_contours;*/

//}

Contour removeBumps(Contour contours){

	Contour ret;
	ret.hierarchy = contours.hierarchy;
	for(int i = 0; i<contours.contours.size(); i++){
		if(contours.contours[i].size() < 8){
			continue;
		}
		std::vector<Point>  debumpedPoints;
		Rect a = boundingRect(contours.contours[i]);

		double maxEpsilon = a.width + a.height;
		double epsilon = .05;//maxEpsilon / 2;
		double minEpsilon = 0.0;

		approxPolyDP(contours.contours[i], debumpedPoints, epsilon, true);
		int k = 0;
		while(debumpedPoints.size() != 8){
			/*if(debumpedPoints.size() < 8){
				maxEpsilon = epsilon;
				epsilon = (epsilon + minEpsilon)/2 - .01;
			}else{
				minEpsilon = epsilon;
				epsilon = (epsilon + maxEpsilon)/2 + .01;
			}*/
			epsilon += .5;

			debumpedPoints.clear();
			approxPolyDP(contours.contours[i], debumpedPoints, epsilon, true);

			k++;
			if(k > 100){
				break;
			}
		}

		ret.contours.push_back(debumpedPoints);
	}


	return ret;
}

void drawContourPoints(cv::Mat img, Contour contours){
	Scalar color = Scalar(0, 0, 255);
	for(int i = 0; i < contours.contours.size(); i++){
		for(int j = 0; j < contours.contours[i].size(); j++){
			circle(img, contours.contours[i][j], 2, color);
		}
	}
}

std::vector<Point> pickBestContour(Contour contours){
	if(contours.contours.size() == 0){
		std::vector<Point> a;
		return a;
	}
	double* scores = new double[contours.contours.size()];
	for(int i = 0; i<contours.contours.size(); i++){
		double area = contourArea(contours.contours[i]);
		Rect bounding = boundingRect(contours.contours[i]);
		scores[i] = std::abs(((double)(bounding.width)) / bounding.height - 1.492) + std::abs(area/bounding.area() - .3143);
	}

	int maxIndex = 0;
	double minScore = scores[0];
	for(int i = 0; i<contours.contours.size(); i++){
		if(scores[i] < minScore){
		minScore = scores[i];
			maxIndex = i;
		}
	}

	delete[] scores;

	return contours.contours[maxIndex];
}

Contour findCornersFromContour(Contour contours, double cutoffAngle){
	double cosOfCutoffAngle = std::cos((long double) cutoffAngle);

	std::vector<std::vector<Point>> newContours;
	for(int i = 0; i < contours.contours.size(); i++){
		if(contours.contours[i].size() < 8){
			continue;
		}
		std::vector<Point> corners;

		double* cosOfAngles = new double[contours.contours[i].size() - 1];

		for(int j = 0; j < contours.contours[i].size() - 1; j++){

			double v0x, v0y;
			if(j == 0){
				v0x = contours.contours[i][j].x - contours.contours[i][contours.contours[i].size() - 2].x; //because it has the first and last point same
				v0y = contours.contours[i][j].y - contours.contours[i][contours.contours[i].size() - 2].y;
			}else{
				v0x = contours.contours[i][j].x - contours.contours[i][j-1].x;
				v0y = contours.contours[i][j].y - contours.contours[i][j-1].y;
			}


			double v1x = contours.contours[i][j+1].x - contours.contours[i][j].x;
			double v1y = contours.contours[i][j+1].y - contours.contours[i][j].y;




			cosOfAngles[j] = ((v1x * v0x) + (v1y * v0y)) / std::sqrt((long double)((v1x*v1x + v1y*v1y) * (v0x*v0x + v0y*v0y)));

			//if(cosOfAngle < cosOfCutoffAngle){
			//	corners.push_back(contours.contours[i][j]);
			//}

		}

		struct Comp{
		    Comp( double* v ) : _v(v) {}
		    bool operator ()(int a, int b) { return _v[a] > _v[b]; }
		    const double* _v;
		};

		std::vector<int> indexArray;
		indexArray.resize(contours.contours[i].size() - 1);
		for( int k= 0; k<contours.contours[i].size() - 1; k++ ){
			indexArray[k]= k;
		}

		partial_sort( indexArray.begin(), indexArray.begin()+8, indexArray.end(), Comp(cosOfAngles) );

		for(int k = 0; k < 8; k++){
			corners.push_back(contours.contours[i][k]);
		}

		corners.push_back(corners.front());
		newContours.push_back(corners);
		delete[] cosOfAngles;






	}

	Contour ret;
	ret.contours = newContours;
	ret.hierarchy = contours.hierarchy;

	return ret;
}


