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
#include <networkbase.h>
#include <boost/thread.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "session.h"
#include "message.h"
#include "directory.h"
#ifndef SERVER_H
#define SERVER_H

class Server:public Networkbase
{
private:
  std::vector<Session*> sessions;
  std::vector<sockaddr_in> _clientadresses;
  std::map<int, Directory*> user_directories;
  Directory& rootdirectory_;
  
public:
  Server(NetworkAddressType, NetworkProtocolType,int, Directory &);
  void waitforincome();
  ~Server();
private:  
  void createdirectory();
  void startsession(int);
  Message * deserializemessage(char* msg);
  void executecommand(Message * message);
};


#endif // SERVER_H
