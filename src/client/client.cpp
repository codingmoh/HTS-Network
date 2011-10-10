#include <string.h>
#include "client.h"
#include <listmessage.h>

Client::Client(NetworkAddressType addresstype, 
	       NetworkProtocolType protocoltype, 
	       int port, std::string username):
	       Networkbase(addresstype, protocoltype, port), username(username)
{
 
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
   Serializer::sendmessage(this->socket_descriptor, message);
}
void Client::waitresponse()
{
  Message * message = Serializer::receivemessage(this->socket_descriptor, 2048);
  this->executecommand(message);
}

void Client::executecommand(Message*& message)
{
  std::cout<<"got back"<<std::endl;
  std::cout<<message->getmessagetype()<<std::endl;
  if(message->getmessagetype()==Message::mList)
  {
    std::vector<ListMessageElement> elem = dynamic_cast<Listmessage*>(message)->GetElements();
    for(int i = 0; i< elem.size(); i++)
    {
      std::cout<<elem[i]._number<<":"<<elem[i]._subject<<std::endl;
    }
  }
}