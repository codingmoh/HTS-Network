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


#ifndef LISTMESSAGE_H
#define LISTMESSAGE_H
#include "message.h"
//#include "listmessageelement.h"
#include "mail.h"
#include <boost/serialization/vector.hpp>
//#include <boost/serialization/string.hpp>
#include <vector>

class Listmessage: public Message
{
   //typedef std::pair<std::string, int> ListMessageElement;
   friend class boost::serialization::access;
   std::string username_;
  // std::vector<ListMessageElement > elements_;
   std::vector<std::string> elements_;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
     boost::serialization::base_object<Message>(*this);
      ar & elements_;
      ar & username_;
      
   }
  
public:
   Listmessage(std::string user):Message(Message::mList), username_(user)
   {
  
   }
   Listmessage():Message(Message::mList)
   {
     
   }
   
   //void AddElement(ListMessageElement&);
   void AddElement(std::string);
   void AddElement(Mail);
   //std::vector<ListMessageElement> GetElements();
   std::vector<std::string> GetElements();
   std::string GetUserName();
};
//BOOST_CLASS_EXPORT(Listmessage);
#endif // LISTMESSAGE_H
