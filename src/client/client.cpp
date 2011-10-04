#include "client.h"
#include <string.h>

Client::Client(NetworkAddressType addresstype, NetworkProtocolType protocoltype, int port, std::string username):Networkbase(addresstype, protocoltype, port)
{
 this->username =  username;
}

bool Client::connect_to_target(std::string ip)
{
  sockaddr_in addr;
  inet_aton (ip.c_str(), &this->addr.sin_addr);
 if(connect(this->socket_descriptor, (sockaddr *) &this->addr, sizeof(this->addr)) == 0)
   return true;
 else
   return false;
}

void Client::sendmessage(Message *& message)
{
  const char * serializedmessage = this->serializemessage(message);
  send(this->socket_descriptor,serializedmessage, strlen(serializedmessage),0);
}
const char* Client::serializemessage(Message *& message)
{
  std::stringstream ss;
  boost::archive::text_oarchive oa(ss);
  oa << message;
  return ss.str().c_str();
}