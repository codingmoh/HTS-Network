

#ifndef SESSION_H
#define SESSION_H

#include "mail.h"
#include <boost/thread.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "directory.h"
#include "ldaplogin.h"
#include "serializer.h"
#include "listmessage.h"
#include "messageexception.h"
#include "read.h"
#include "login.h"
#include <standard_messages.h>
#include <deletemessage.h>

class Session: public Serializer
{
private:
  int socketid_;
  void startrecieveing();
  bool loggedin_;
  //Message * deserializemessage(char* msg);
  void executecommand(Message *& message);
  boost::thread * sessionthread_;
  Directory userdir_;
  Ldaplogin& ldaplogin_;
public:
  Session(int, Directory, Ldaplogin& );
  void start();
  ~Session();
};
#endif 
