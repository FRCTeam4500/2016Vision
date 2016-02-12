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

#ifndef _VIDEOIO_HPP
#define _VIDEOIO_HPP
#include <opencv2/videoio.hpp>
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
	/*int change = 1;
	//for(int n = 0; n < 700; n++){
	for(int n = 0; true; n = properModulus(n + change, 600)){
		Mat image;
		image = getFieldImage(n);



		Scalar color(0, 0, 255);

		if(image.data){
			printf("%d:  ", n);
			ImageReport report = getImageReport(image);





			circle(image, report.center, 3, color, 3);
			drawContourList(image, report.bestContour);
			imshow("image", image);
			int key = waitKey(0);

			if((key & 0xFF) == 'q'){
				change = -1;

			}
			if((key & 0xFF) == 'w'){
				change = 1;
			}

			if((key & 0xFF) == 'e'){
				break;
			}

		}
	}*/
	VideoCapture usbCam(1);

	usbCam.set(CV_CAP_PROP_BRIGHTNESS, .05);

	/*int rmin = 0, rmax = 257, gmin = 0, gmax = 257, bmin = 0, bmax = 257;
	namedWindow("Trackbar", 1);
	createTrackbar("rmin", "Trackbar", &rmin, 257);
	createTrackbar("rmax", "Trackbar", &rmax, 257);
	createTrackbar("gmin", "Trackbar", &gmin, 257);
	createTrackbar("gmax", "Trackbar", &gmax, 257);
	createTrackbar("bmin", "Trackbar", &bmin, 257);
	createTrackbar("bmax", "Trackbar", &bmax, 257);*/


	Mat img;
	while(true){

		usbCam.read(img);
		//Mat output = multipleThresholdRGB(img, rmin-1, rmax, gmin-1, gmax, bmin-1, bmax);


		//imshow("output", output);

		ImageReport report = getImageReport(img);

		drawContourList(img, report.bestContour);
		circle(img, report.center, 3, Scalar(0, 0, 255), 3);
		imshow("image", img);

		int key = waitKey(1);

		if((key&0xFF) == 113){
			break;
		}



	}



	return 0;
}


