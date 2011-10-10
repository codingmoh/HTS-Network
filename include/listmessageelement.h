#include <string>
#include <boost/serialization/access.hpp>
//#include "listmessage.h"

#ifndef LISTMESSAGEELEMENT_H
#define LISTMESSAGEELEMENT_H
class ListMessageElement
{ 
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
      ar & _subject;
      ar & _number;
   }
public:
  std::string _subject;
  int _number;
public:
  ListMessageElement(){}
  ListMessageElement(std::string, int);
};

#endif