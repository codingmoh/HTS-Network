#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "networkbase.h"
#ifndef CLIENT_H
#define CLIENT_H

class Client:public Networkbase
{
  Client();
};

#endif // CLIENT_H
