/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <exception>
#include <iostream>
#ifndef NETWORKBASE_H
#define NETWORKBASE_H

class Networkbase
{
public:
  enum NetworkProtocolType
  {
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM,
    RAW = SOCK_RAW
  };
  enum NetworkAddressType
  {
    IPv4 = AF_INET,
    IPv6 = AF_INET6,
    UDS = AF_LOCAL 
  };
  
Networkbase(NetworkAddressType, NetworkProtocolType, int);
protected:
    sockaddr_in addr;
    int socket_descriptor;
};

#endif // NETWORKBASE_H
