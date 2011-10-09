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
      mList
    };
    
  public:
    Message(Message::Messagetype type)
    {
      this->_msg_type = type;
    };
    Message(){};
    
    Messagetype getmessagetype()
    {
      return _msg_type;
    };
    virtual ~Message()
    {
      
    };
    
  private:  
      Messagetype _msg_type;
      friend class boost::serialization::access;   
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
	ar & _msg_type;
      }
};
#endif

