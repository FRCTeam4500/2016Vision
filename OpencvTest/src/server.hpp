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


void serve(ImageReport** report);

#endif /* SRC_SERVER_HPP_ */
