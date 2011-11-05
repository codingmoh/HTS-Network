
#ifndef DELETEMESSAGE_H
#define DELETEMESSAGE_H
#include "message.h"

class Deletemessage: public Message
{
   friend class boost::serialization::access;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
      boost::serialization::base_object<Message>(*this);
      ar & number_;
      ar & user_;
   }

   

public:
   int number_;
   std::string user_;
   Deletemessage(int nr, std::string name) :
         Message(Message::mDelete), number_(nr), user_(name)
   {
   }

   Deletemessage(): Message(Message::mDelete)
   {

   }
};

//BOOST_CLASS_EXPORT(Deletemessage);
#endif // SERVER_H
