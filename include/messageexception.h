#include "message.h"
#ifndef MESSAGEEXCEPTION_H
#define MESSAGEEXCEPTION_H

class MessageException : public Message
{
    friend class boost::serialization::access;
    template<class Archive>
    void
    serialize(Archive & ar, const unsigned int version)
    {
        boost::serialization::base_object<Message>(*this);
        ar & err_;
        ar & msg_;
    }

public:
    std::string err_;
    std::string msg_;
    int number_;
    MessageException(std::string err , std::string msg) :
            Message(Message::mException), err_(err), msg_(msg)
    {

    }

    MessageException() : Message(Message::mException)
    {

    }
};

BOOST_CLASS_EXPORT(MessageException);
#endif
