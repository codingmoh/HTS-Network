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
#include <listmessage.h>

const char* Serializer::serializemessage(Message *& message)
{
  std::stringstream ss;
  boost::archive::text_oarchive oa(ss);
  std::cout<<message->getmessagetype()<<std::endl;
  oa << message;
  return ss.str().c_str();
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
  const char * serializedmessage = serializemessage(message);
  send(socket_id, serializedmessage, strlen(serializedmessage),0);
}

Message* Serializer::receivemessage(int socket_id, int buffer)
{
  char buf[buffer];
  recv(socket_id, &buf, buffer-1, 0);
  return this->deserializemessage(buf);  
}