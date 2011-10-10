#include "mail.h"
#include <boost/thread.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "directory.h"
#include "serializer.h"
#include "listmessage.h"
#include "messageexception.h"
#ifndef SESSION_H
#define SESSION_H

class Session: public Serializer
{
private:
  int socketid_;
  void startrecieveing();
  //Message * deserializemessage(char* msg);
  void executecommand(Message *& message);
  Directory &userdir_;
public:
  Session(int socketid,Directory &);
  void start();
  ~Session();
};
#endif 
