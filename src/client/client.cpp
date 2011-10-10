#include <string.h>
#include "client.h"
#include <listmessage.h>
#include <messageexception.h>

Client::Client(NetworkAddressType addr_esstype,
    NetworkProtocolType protocoltype, int port, std::string username) :
  Networkbase(addr_esstype, protocoltype, port)
{

}

bool
Client::connect_to_target(std::string ip)
{
  sockaddr_in addr_;
  inet_aton(ip.c_str(), &this->addr_.sin_addr);
  if (connect(this->socket_descriptor_, (sockaddr *) &this->addr_,
      sizeof(this->addr_)) == 0)
    return true;
  else
    return false;
}

void
Client::sendmessage(Message *& message)
{
  Serializer::sendmessage(this->socket_descriptor_, message);
}
void
Client::waitresponse()
{
  Serializer::receivemessage(this->socket_descriptor_, 2048);
}

void
Client::executecommand(Message*& message)
{

  std::cout << message->getmessagetype() << std::endl;
  if (message->getmessagetype() == Message::mList)
    {
      std::vector<ListMessageElement> elem =
          dynamic_cast<Listmessage*> (message)->GetElements();
      for (int i = 0; i < elem.size(); i++)
        {
          std::cout << elem[i].number_ << ":" << elem[i].subject_ << std::endl;
        }
    }
  else if (message->getmessagetype() == Message::mException)
    {
      std::cout << dynamic_cast<MessageException*> (message)->err_ << ": "
          << dynamic_cast<MessageException*> (message)->msg_ << std::endl;
    }
}
