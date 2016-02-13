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




	std::cout << "Setting up the structs..."  << std::endl;


	ssize_t bytes_recieved;
	char incomming_data_buffer[1];
	bytes_recieved = recv(new_sd, incomming_data_buffer, 1, 0);
	// If no data arrives, the program will just wait here until some data arrives.
	if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
	if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;




	std::cout << "send()ing back a message..."  << std::endl;
	char *msg = "thank you.";
	int len;
	ssize_t bytes_sent;
	len = strlen(msg);
	bytes_sent = send(new_sd, msg, len, 0);

	std::cout << "Stopping server..." << std::endl;
	freeaddrinfo(host_info_list);
	close(new_sd);
	close(socketfd);

}

