#include "mail.h"
#include <boost/thread.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#ifndef SESSION_H
#define SESSION_H
class Session
{
private:
  int socketid;
  void startrecieveing();
  Message * deserializemessage(char* msg);
  void executecommand(Message * message);
public:
  Session(int socketid);
  void start();
  ~Session();
};
#endif 