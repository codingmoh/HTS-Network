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
      ar & subject_;
      ar & number_;
   }
public:
  std::string subject_;
  int number_;
public:
  ListMessageElement(){}
  ListMessageElement(std::string, int);
};

#endif