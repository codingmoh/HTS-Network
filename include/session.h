#include "mail.h"
#include <boost/thread.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "directory.h"
#ifndef SESSION_H
#define SESSION_H
class Session
{
private:
  int socketid;
  void startrecieveing();
  Message * deserializemessage(char* msg);
  bool executecommand(Message * message);
  Directory &userdir;
public:
  Session(int socketid,Directory &);
  void start();
  ~Session();
};
#endif 
