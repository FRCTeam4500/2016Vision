/*
 * SocketServer.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: aditya
 */

#include "SocketServer.h"



SocketServer::SocketServer(std::string port) {

	// The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
	// to by hints must contain either 0 or a null pointer, as appropriate." When a struct
	// is created in c++, it will be given a block of memory. This memory is not necessary
	// empty. Therefore we use the memset function to make sure all fields are NULL.
	memset(&host_info, 0, sizeof host_info);

	host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
	host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
	host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

	this->port = port;

	// Now fill up the linked list of host_info structs with google's address information.
	status = getaddrinfo(NULL, port, &host_info, &host_info_list);


	this->socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
						host_info_list->ai_protocol);

	int yes = 1;
	status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);

	socklen_t addr_size = sizeof(their_addr);

	last_int = 0;

}

void SocketServer::listen(int n){
	status =  listen(socketfd, n);
}

void SocketServer::accept(){
	new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
}

bool SocketServer::recieveInt(){
	ssize_t bytes_recieved;
	int incomming_int;

	bytes_recieved = recv(new_sd, &incomming_int, 4, 0);

	incomming_int = ntohl(incomming_int);

	last_int = incomming_int;

	// If no data arrives, the program will just wait here until some data arrives.
	if (bytes_recieved == 0 || bytes_recieved == -1){
		return false;
	}

	return true;

}

int SocketServer::getLastInt(){
	return last_int;
}


SocketServer::~SocketServer() {
	// TODO Auto-generated destructor stub
}

