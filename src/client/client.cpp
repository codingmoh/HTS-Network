#include "client.h"

void Client::connect_to_target(sockaddr * target_addr)
{
  connect(this->socket_descriptor, target_addr, sizeof(target_addr) );
}