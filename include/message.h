#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#ifndef MESSAGE_H
#define MESSAGE_H
class Message
{  
  public:
    enum Messagetype
    {
      mMail,
      mList,
      mException
    };
    
  public:
    Message(Message::Messagetype type)
    {
      this->msg_type_ = type;
    };
    Message(){};
    
    Messagetype getmessagetype()
    {
      return msg_type_;
    };
    virtual ~Message()
    {
      
    };
    
  private:  
      Messagetype msg_type_;
      friend class boost::serialization::access;   
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
	ar & msg_type_;
      }
};
#endif

