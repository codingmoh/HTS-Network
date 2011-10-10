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

#ifndef STANDARD_MESSAGES_H
#define STANDARD_MESSAGES_H
#include "message.h"
class standard_messages:public Message
{
private:
  
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
      boost::serialization::base_object<Message>(*this);
      ar & type_;
  }
public:
  enum messagetype
  {
    OK,
    ERR,
    EXIT
  };
  messagetype type_;
  standard_messages(messagetype type):Message(Message::mStandard)
  {
   this->type_ = type; 
  }
  standard_messages():Message(Message::mStandard)
  {
    
  }
};

BOOST_CLASS_EXPORT(standard_messages);
#endif // STANDARD_MESSAGES_H
