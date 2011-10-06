#include "message.h"
#ifndef MAIL_H
#define MAIL_H
class Mail:public Message
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
    };
 public:
    std::string _receiver;
    std::string _sender;
    std::string _subject;
    std::string _msg;
    Mail(std::string rec,std::string send,std::string sub,std::string msg):Message(Message::mMail)
    {
      this->_receiver = rec;
      this->_sender = send;
      this->_subject = sub;
      this->_msg = msg;
    }
    Mail():Message(Message::mMail)
    {
      
    }
};
BOOST_CLASS_EXPORT(Mail);
#endif // SERVER_H