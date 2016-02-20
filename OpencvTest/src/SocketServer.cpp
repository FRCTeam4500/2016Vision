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
	status = getaddrinfo(NULL, port.c_str(), &host_info, &host_info_list);


	this->socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
						host_info_list->ai_protocol);

	int yes = 1;
	status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);

	addr_size = sizeof(their_addr);

	last_char = 0;

}

void SocketServer::listen(int n){
	status =  ::listen(socketfd, n);
}

void SocketServer::accept(){
	new_sd = ::accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
}

bool SocketServer::recieveByte(){
	ssize_t bytes_recieved;
	char incomming_char;

	bytes_recieved = recv(new_sd, &incomming_char, 1, 0);



	// If no data arrives, the program will just wait here until some data arrives.
	if (bytes_recieved == 0 || bytes_recieved == -1){
		return false;
	}
	last_char = incomming_char;
	return true;

}

void SocketServer::sendDouble(double data){
	char * doubleString = (char *)(&data);
	ssize_t bytes_sent = send(new_sd, doubleString, 8, 0);
}

char SocketServer::getLastByte(){
	return last_char;
}

void SocketServer::closeClient(){
	close(new_sd);
}


SocketServer::~SocketServer() {
	::freeaddrinfo(host_info_list);
	close(socketfd);
	closeClient();
}

int SocketServer::recieveString(char * buf, int len){
	return recv(new_sd, buf, len, 0);

}

bool SocketServer::sendall(char * buf, int len){
	while (len > 0){
		int i = send(new_sd, buf, len, 0);
		if (i < 1){
			return false;
		}
		buf += i;
		len -= i;
	}
	return true;
}

/*bool SocketServer::connected(){
     char buf;
     int err = recv(new_sd, &buf, 1, MSG_PEEK);
     if(err == SOCKET_ERROR){
          if(WSAGetLastError() != WSAEWOULDBLOCK){
        	  return false;
          }
     }
     return true;
}*/
