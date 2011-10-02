#include "client.h"

Client::Client(NetworkAddressType addresstype, NetworkProtocolType protocoltype, int port ):Networkbase(addresstype, protocoltype, port)
{
  
}

void Client::connect_to_target(std::string ip)
{
  sockaddr_in addr;
  inet_aton (ip.c_str(), &this->addr.sin_addr);
  connect(this->socket_descriptor, (sockaddr *) &this->addr, sizeof(this->addr) ); 
}