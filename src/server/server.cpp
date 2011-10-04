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

#include "server.h"
#include <message.h>
#include <mail.h>

Server::Server(NetworkAddressType networktype, NetworkProtocolType protocoltype, int port ):Networkbase(networktype,protocoltype,port)
{
  bind(this->socket_descriptor, (struct sockaddr*) &this->addr,sizeof(this->addr));
  listen(this->socket_descriptor, 5);
}

void Server::waitforincome()
{
  sockaddr_in client_addr;
  socklen_t addrlen;
  int new_socket;
  while( (new_socket = accept(this->socket_descriptor,(struct sockaddr *) &client_addr, &addrlen)) < 1);
  std::cout<<"client connected"<<std::endl;
  boost::thread sessionthread(&Server::startsession, this, new_socket);
  this->_sessions.push_back(&sessionthread);
  sessionthread.join();
  this->waitforincome();
}

void Server::startsession(int session_socket_descriptor)
{
  char buf[2048];
  recv(session_socket_descriptor, &buf, 2047, 0);
  std::cout<<"message received"<<std::endl;
  deserializemessage(buf);
  this->executecommand(this->deserializemessage(buf));
}

Message * Server::deserializemessage(char* msg)
{
  Message * mesg;
  std::stringstream ss(msg);
  boost::archive::text_iarchive ia(ss);
  ia >> mesg;
  return mesg;
}

void Server::executecommand(Message * message)
{
 if(message->getmessagetype()==Message::mMail)
 {
   std::cout<<"Mail:"<<dynamic_cast<Mail*>(message)->_msg<<std::endl;
 }
}