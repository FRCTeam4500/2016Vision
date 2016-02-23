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

#ifndef _INCLUDE_VIDEOIO_HPP
#define _INCLUDE_VIDEOIO_HPP
#include <opencv2/videoio.hpp>
#endif

#ifndef _INCLUDE_STRING
#define _INCLUDE_STRING
#include <string>
#endif

#ifndef _INCLUDE_STDLIB
#define _INCLUDE_STDLIB
#include <stdlib.h>
#endif

#ifndef _INCLUDE_UTILITIES_HPP
#define _INCLUDE_UTILITIES_HPP
#include "Utilities.hpp"
#endif

#ifndef _INCLUDE_SERVER_HPP
#define _INCLUDE_SERVER_HPP
#include "server.hpp"
#endif

#ifndef _INCLUDE_IOSTREAM
#define _INCLUDE_IOSTREAM
#include <iostream>
#endif

#ifndef _INCLUDE_CSTRING
#define _INCLUDE_CSTRING
#include <cstring>      // Needed for memset
#endif

#ifndef _INCLUDE_SOCKET_H
#define _INCLUDE_SOCKET_H
#include <sys/socket.h> // Needed for the socket functions
#endif

#ifndef _INCLUDE_NETDB_H
#define _INCLUDE_NETDB_H
#include <netdb.h>      // Needed for the socket functions
#endif


#ifndef _INCLUDE_THREAD
#define _INCLUDE_THREAD
#include <thread>
#endif

using namespace cv;

struct DoubleReportBuffer{
	bool first = true;
	ImageReport firstReport;
	ImageReport secondReport;
	ImageReport * location;
	void set(ImageReport a){
		if(first){
			first = false;
			firstReport = a;
			location = &firstReport;
		}else{
			first = true;
			secondReport = a;
			location = &secondReport;
		}
	}
};

int main( int argc, char** argv ){
	DoubleReportBuffer reportBuffer;

	std::thread server_thread (serve, &reportBuffer.location);
	server_thread.detach();

	std::thread serverMJPEG_thread (serveMJPEG, &reportBuffer.location);
	serverMJPEG_thread.detach();

	VideoCapture usbCam(1);

	usbCam.set(CV_CAP_PROP_BRIGHTNESS, .1);
	Mat img;
	ImageReport r;
	r.angles = Point2d(0.0, 0.0);
	reportBuffer.set(r);
	while(true){
		usbCam.read(img);

		//imshow("image", img);

		//int key = waitKey(1);

		//if((key&0xFF) == 113){
		//	break;
		//}

		ImageReport report = getImageReport(img);

		reportBuffer.set(report);





	}




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


	/*int rmin = 0, rmax = 257, gmin = 0, gmax = 257, bmin = 0, bmax = 257;
	namedWindow("Trackbar", 1);
	createTrackbar("rmin", "Trackbar", &rmin, 257);
	createTrackbar("rmax", "Trackbar", &rmax, 257);
	createTrackbar("gmin", "Trackbar", &gmin, 257);
	createTrackbar("gmax", "Trackbar", &gmax, 257);
	createTrackbar("bmin", "Trackbar", &bmin, 257);
	createTrackbar("bmax", "Trackbar", &bmax, 257);*/


	/*
	VideoCapture usbCam(1);

	usbCam.set(CV_CAP_PROP_BRIGHTNESS, .05);
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



	}*/



	return 0;
}


