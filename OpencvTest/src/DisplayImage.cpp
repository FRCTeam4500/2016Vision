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

#ifndef _UTILITIES_HPP
#define _UTILITIES_HPP
#include "Utilities.hpp"
#endif


using namespace cv;



int main( int argc, char** argv ){

	for(int n = 0; n<700; n++){
		Mat image;
		image = getFieldImage(n);

		if(image.data){

			Mat output = multipleThreshold(image, 0, 255, 69, 255, 0, 255);
			Mat binaryImage(output.size(), CV_8UC3);
			removeHoles(output);
			output.copyTo(binaryImage);



			Contour c = findContoursFromBinary(output);
			Contour d = filterContours(c, 200.0, 0, 0, 1000, 0, 1000, .42);

			drawContourList(d, image);
			saveImage(n, image, binaryImage);
			printf("%d %d\n", n, d.contours.size());

		}
	}



	return 0;
}
