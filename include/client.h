#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include "message.h"
#include "serializer.h"
#include "networkbase.h"
#include "mail.h"
#include <string.h>
#include <listmessage.h>
#include <standard_messages.h>
#include <messageexception.h>


class Client : public Networkbase, public Serializer
{
private:
  std::string username_;
  //const char * serializemessage(Message *& message);
public:
  bool loggedIn;
  Client(NetworkAddressType, NetworkProtocolType, int, std::string);
  bool connect_to_target(std::string);
  std::string getusername();	
  void sendmessage(Message*&);
  void waitresponse();
  void executecommand(Message*&);
  void closeconnection();
};

#endif // CLIENT_H
