#include "message.h"
#ifndef READ_H
#define READ_H

class Read: public Message
{
   friend class boost::serialization::access;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
      boost::serialization::base_object<Message>(*this);
      ar & user_;
      ar & number_;
   }



public:
   std::string user_;
   int number_;
   Read(std::string user, int number) :
         Message(Message::mRead), user_(user), number_(number)
   {

   }

   Read(): Message(Message::mRead)
   {

   }
};

BOOST_CLASS_EXPORT(Read);
#endif // SERVER_H
