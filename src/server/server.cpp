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

#include <server.h>
#include <message.h>
#include <mail.h>

Server::Server(NetworkAddressType networktype, NetworkProtocolType protocoltype,int port, Directory & rootdir, Ldaplogin & ldap):
	       Networkbase(networktype,protocoltype,port), rootdirectory_(rootdir), ldaplogin_(ldap)
{
  bind(this->socket_descriptor_, 
       (struct sockaddr*) &this->addr_,sizeof(this->addr_));
  listen(this->socket_descriptor_, 5);
}
void Server::waitforincome()
{
  sockaddr_in client_addr;
  socklen_t addrlen;
  int new_socket;
  while((new_socket = accept(this->socket_descriptor_,(struct sockaddr *) &client_addr, &addrlen))< 1);
  std::cout<<"client connected"<<std::endl;
  Session *  session = new Session(new_socket,this->rootdirectory_, this->ldaplogin_);
 // sessions.push_back(session);
  session->start();
  //close(this->socket_descriptor_);
  this->waitforincome();
}


Server::~Server()
{
  //KILL SESSIONS
}
