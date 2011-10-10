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
      ar & _msg;
      ar & _receiver;
      ar & _sender;
      ar & _subject;
      ar & _number;
   }

   

public:
   std::string _receiver;
   std::string _sender;
   std::string _subject;
   std::string _msg;
   int _number;
   Mail(std::string rec, std::string send, std::string sub, std::string msg) :
         Message(Message::mMail), _receiver(rec), _sender(send), _subject(sub), _msg(msg)
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
