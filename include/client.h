#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "serializer.h"
#include "networkbase.h"
#include "mail.h"


#ifndef CLIENT_H
#define CLIENT_H



class Client : public Networkbase, public Serializer
{
private:
  std::string username_;
  //const char * serializemessage(Message *& message);
public:
  Client(NetworkAddressType, NetworkProtocolType, int, std::string);
  bool connect_to_target(std::string);
  std::string getusername();	
  void sendmessage(Message*&);
  void waitresponse();
  void executecommand(Message*&);
  void closeconnection();
};

#endif // CLIENT_H
