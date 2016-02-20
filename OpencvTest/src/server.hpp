/*
 * server.h
 *
 *  Created on: Feb 12, 2016
 *      Author: aditya
 */

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

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

#ifndef _INCLUDE_SOCKETSERVER_H
#define _INCLUDE_SOCKETSERVER_H
#include "SocketServer.h"
#endif

#define TEXT_RESPONSE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: Closed\r\n<html><body><img src=\"http://localhost:4321/a.mjpeg\"></body></html>"
#define JPEG_RESPONSE "HTTP/1.0 200 OK\r\nServer: en.code-bude.net example server\r\nCache-Control: no-cache\r\nCache-Control: private\r\nContent-Type: multipart/x-mixed-replace;boundary=--boundary188fw98t89asdf98adsf\r\n\r\n"
#define JPEG_HEADER "--boundary188fw98t89asdf98adsf\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n"


void serve(ImageReport** report);
void serveMJPEG(ImageReport** report);
bool contains(char* s1, int len1, char* s2, int len2);

#endif /* SRC_SERVER_HPP_ */
