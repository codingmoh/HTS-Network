#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "networkbase.h"
#ifndef CLIENT_H
#define CLIENT_H
#include "message.h"

class Client : public Networkbase
{
public:
  Client(NetworkAddressType , NetworkProtocolType , int );
  void connect_to_target(sockaddr * target_addr);
  void send(Message*);
};

#endif // CLIENT_H
