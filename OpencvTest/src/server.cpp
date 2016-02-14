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



#define PORTNUM 1234

void serve(ImageReport** report){
	SocketServer s("1234");
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

