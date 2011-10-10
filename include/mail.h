#include "message.h"
#ifndef MAIL_H
#define MAIL_H

class Mail: public Message
{
   friend class boost::serialization::access;
   template<class Archive>
   void serialize(Archive & ar, const unsigned int version)
   {
      boost::serialization::base_object<Message>(*this);
      ar & msg_;
      ar & receiver_;
      ar & sender_;
      ar & subject_;
      ar & number_;
   }

   

public:
   std::string receiver_;
   std::string sender_;
   std::string subject_;
   std::string msg_;
   int number_;
   Mail(std::string rec, std::string send, std::string sub, std::string msg) :
         Message(Message::mMail), receiver_(rec), sender_(send), subject_(sub), msg_(msg)
   {
      /*this->_receiver = rec;
      this->_sender = send;
      this->_subject = sub;
      this->_msg = msg;*/
   }

   Mail(): Message(Message::mMail)
   {

   }
};

BOOST_CLASS_EXPORT(Mail);
#endif // SERVER_H
