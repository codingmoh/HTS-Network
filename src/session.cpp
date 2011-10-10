#include <session.h>


Session::Session(int socketid, Directory& userdir):userdir(userdir), socketid(socketid)
{
  
}

void Session::start()
{
  boost::thread sessionthread(&Session::startrecieveing, this);
  sessionthread.join();
}

void Session::startrecieveing()
{
  
  if( this->executecommand(Serializer::receivemessage(this->socketid, 2048)))
  {
    //SEND OK
  }
  else
  {
    //SEND ERR
  }
}

bool Session::executecommand(Message * message)
{
 if(message->getmessagetype()==Message::mMail)
 {
   this->userdir.savemessage(*dynamic_cast<Mail*>(message));
 }
 else if(message->getmessagetype()==Message::mList)
 {
   std::cout<<"gothere"<<std::endl;
   Listmessage * lm = dynamic_cast<Listmessage*>(message);
   std::cout<<lm->GetUserName()<<std::endl;
   this->userdir.getmessages(*lm);
   Message * msg = lm;
   std::cout<<lm->GetElements()[0]._subject<<std::endl;
   Serializer::sendmessage(this->socketid, msg );// ^^ ...OOP FTW xD
 }
 this->startrecieveing();
}
Session::~Session()
{
  //KILL THREADS
}
