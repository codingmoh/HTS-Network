#include "message.h"
#ifndef LOGIN_H
#define LOGIN_H

class Login: public Message
{
   friend class boost::serialization::access;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
      boost::serialization::base_object<Message>(*this);
      ar & user_;
      ar & password_;
   }



public:
   std::string user_;
   std::string password_;
   Login(std::string us, std::string pw) :
         Message(Message::mLogin), user_(us), password_(pw)
   {

   }

   Login(): Message(Message::mLogin)
   {

   }
};

BOOST_CLASS_EXPORT(Login);
#endif // SERVER_H
