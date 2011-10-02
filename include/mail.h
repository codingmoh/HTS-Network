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
    };
  public:
    std::string _msg;
    Mail():Message(Message::mMail)
    {
      
    }
   
};
BOOST_CLASS_EXPORT(Mail);
#endif // SERVER_H