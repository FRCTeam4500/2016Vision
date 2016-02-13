/*
 * SocketServer.h
 *
 *  Created on: Feb 13, 2016
 *      Author: aditya
 */

#ifndef SRC_SOCKETSERVER_H_
#define SRC_SOCKETSERVER_H_

#ifndef _INCLUDE_STRING
#define _INCLUDE_STRING
#include <string>
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

public:

	SocketServer(std::string port);

	void listen(int n);
	void accept();
	bool recieveInt();
	int getLastInt();


	virtual ~SocketServer();
};

#endif /* SRC_SOCKETSERVER_H_ */
