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

#include "serializer.h"
#include "EXPORTS.h"

std::string Serializer::serializemessage(Message *& message)
{
  std::stringstream ss;
  boost::archive::text_oarchive oa(ss);
  oa << message;
  std::cout<<"size of str:"<<ss.str().size()<<std::endl;
  std::cout<<ss.str()<<std::endl;
  //ss<<'\0';
  std::string ssst =  ss.str();
//   const char * sstr = new char(str.c_str());
//   char arr[2048];
//   ssst.copy(arr,ssst.size());
//   std::cout<<"size char"<<strlen(sstr)<<std::endl;
//   std::cout<<arr<<std::endl;
  return ssst;
}

Message * Serializer::deserializemessage(char* msg)
{
  Message * mesg;
  std::stringstream ss(msg);
  boost::archive::text_iarchive ia(ss);
  ia >> mesg;
  return mesg;
}

void Serializer::sendmessage(int socket_id, Message*& message)
{
  int x = 0;
  while(x==0)
  {
    std::string serializedmessage = serializemessage(message);
    
    std::cout<<"SENDING:"<<serializedmessage<<std::endl;
    x = send(socket_id, serializedmessage.c_str(), serializedmessage.length(), 0);
    usleep(300000);
    std::cout<<"VAL "<<x<<std::endl;
  }
  std::cout<<"return Val:"<<x<<std::endl;
}

Message* Serializer::receivemessage(int socket_id, int buffer)
{

  char buf[buffer];
  recv(socket_id, &buf, buffer-1, 0);
  Message * m = this->deserializemessage(buf);
  executecommand(m);  
}
