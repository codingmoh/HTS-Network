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

#ifndef SERVER_H
#define SERVER_H
#include <networkbase.h>
#include <boost/thread.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "session.h"
#include "message.h"
#include "directory.h"
#include "ldaplogin.h"
class Server:public Networkbase
{
private:
  std::vector<Session*> sessions_;
  std::vector<sockaddr_in> clientadresses_;
  std::map<int, Directory*> user_directories_;
  Directory& rootdirectory_;
  Ldaplogin& ldaplogin_;
  bool stop_;
  boost::mutex m_mutex_;
  boost::condition_variable cond;
public:
  Server(NetworkAddressType, NetworkProtocolType,int, Directory &, Ldaplogin &);
  void startlistening();
  ~Server();
private:  
  boost::thread * t_listener_;
  void startsession(int);
  void waitforincome();
};


#endif // SERVER_H
