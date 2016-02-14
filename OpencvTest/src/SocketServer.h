/*
 * SocketServer.h
 *
 *  Created on: Feb 13, 2016
 *      Author: aditya
 */

#ifndef SRC_SOCKETSERVER_H_
#define SRC_SOCKETSERVER_H_

#ifndef _INCLUDE_SOCKET_H
#define _INCLUDE_SOCKET_H
#include <sys/socket.h>
#endif

#ifndef _INCLUDE_NETDB_H
#define _INCLUDE_NETDB_H
#include <netdb.h>
#endif

#ifndef _INCLUDE_UTILITIES_HPP
#define _INCLUDE_UTILITIES_HPP
#include "Utilities.hpp"
#endif

#ifndef _INCLUDE_IOSTREAM
#define _INCLUDE_IOSTREAM
#include <iostream>
#endif

#ifndef _INCLUDE_CSTRING
#define _INCLUDE_CSTRING
#include <cstring>      // Needed for memset
#endif

#ifndef _INCLUDE_UNISTD_H
#define _INCLUDE_UNISTD_H
#include <unistd.h>
#endif



class SocketServer {
private:
	int status;
	struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
	struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
	std::string port;
	int socketfd ; // The socket descripter
	int new_sd;
	struct sockaddr_storage their_addr;
	int last_int;
	socklen_t addr_size;

public:

	SocketServer(std::string port);

	void listen(int n);
	void accept();
	bool recieveInt(); //TODO: Make sure that java is sending ints
	int getLastInt();
	void sendDouble(double data);
	void closeClient();


	virtual ~SocketServer();
};

#endif /* SRC_SOCKETSERVER_H_ */
