/*
 * server.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: aditya
 */


#ifndef _INCLUDE_SERVER_HPP
#define _INCLUDE_SERVER_HPP
#include "server.hpp"
#endif



#define PORTNUM "1234"
#define MJPEG_PORTNUM "4321"

void serve(ImageReport** report){
	SocketServer s(PORTNUM);
	s.listen(5);

	while(true){
		s.accept();
		printf("Accepted\n");
		while(true){

			if(!s.recieveByte()){	//if the client closes the connection
				s.closeClient();
				break;
			}
			printf("Recieved\n");

			int needed = s.getLastByte();
			printf("%d\n", needed);
			if(needed == 0){
				s.sendDouble((*report) -> angles.y);
			}else if(needed == 1){
				s.sendDouble((*report) -> angles.x);
			}else if(needed == 2){
				if((*report) -> goalIsPresent){
					s.sendDouble(0.0);
				}else{
					s.sendDouble(1.0);
				}
			}
		}
	}

}

void serveMJPEG(ImageReport** report){
	SocketServer s(MJPEG_PORTNUM);
	s.listen(5);
	char * buf = (char*)malloc(sizeof(char)*100);
	std::vector<unsigned char> imageBuffer;
	char * headerbuf = (char*) malloc(sizeof(char)*100);
	//std::vector<int> p;
	while(true){
		s.accept();
		int recieved = s.recieveString(buf, 100);
		if(contains(buf, recieved, "mjpeg", 5)){
			s.sendall(TEXT_RESPONSE, strlen(TEXT_RESPONSE));

			s.closeClient();
		}else{
			if(s.sendall(JPEG_RESPONSE, strlen(JPEG_RESPONSE))){
				cv::Mat img = (*report)->image;
				cv::imencode(".jpg", img, imageBuffer);


				int headerLength = sprintf(headerbuf, JPEG_HEADER, imageBuffer.size());



				while(s.sendall(headerbuf, headerLength) && s.sendall((char*)imageBuffer.data(), imageBuffer.size())) {
					cv::Mat img = (*report)->image;
					cv::imencode(".jpg", img, imageBuffer);


					int headerLength = sprintf(headerbuf, JPEG_HEADER, imageBuffer.size());
				}

				s.closeClient();
			}
		}
	}

	free(buf);
	free(headerbuf);
}

bool contains(char* s1, int len1, char* s2, int len2){
	for(int i = 0; i<len1 - len2;i++){
		int j = 0;
		while(j < len2 && s1[i+j] == s2[j]){
			j++;
		}
		if(j == len2){
			return true;
		}
	}

	return false;
}


