#include <session.h>


Session::Session(int socketid)
{
  this->socketid = socketid;
}

void Session::start()
{
  boost::thread sessionthread(&Session::startrecieveing, this);
  sessionthread.join();
}

void Session::startrecieveing()
{
  char buf[2048];
  recv(this->socketid, &buf, 2047, 0);
  this->deserializemessage(buf);
  if( this->executecommand(this->deserializemessage(buf)))
  {
    //SEND OK
  }
  else
    //SEND ERR
}
Message * Session::deserializemessage(char* msg)
{
  Message * mesg;
  std::stringstream ss(msg);
  boost::archive::text_iarchive ia(ss);
  ia >> mesg;
  return mesg;
}

void Session::executecommand(Message * message)
{
 if(message->getmessagetype()==Message::mMail)
 {
   
 }
}
Session::~Session()
{
  //KILL THREADS
}