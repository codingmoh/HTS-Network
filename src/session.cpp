#include <session.h>


Session::Session(int socketid, Directory& userdir):userdir_(userdir), socketid_(socketid)
{
  
}

void Session::start()
{
  boost::thread sessionthread(&Session::startrecieveing, this);
  sessionthread.join();
}

void Session::startrecieveing()
{
  Serializer::receivemessage(this->socketid_, 2048);
   //executecommand();
  /*if()
  {
    //SEND OK
  }
  else
  {
    //SEND ERR
  }*/
}

void Session::executecommand(Message *& message)
{
 if(message->getmessagetype()==Message::mMail)
 {
   this->userdir_.savemessage(*dynamic_cast<Mail*>(message));
 }
 else if(message->getmessagetype()==Message::mList)
 {
   std::cout<<"gothere"<<std::endl;
   Listmessage * lm = dynamic_cast<Listmessage*>(message);
   std::cout<<lm->GetUserName()<<std::endl;
   this->userdir_.getmessages(*lm);
   Message * msg = lm;
   std::cout<<lm->GetElements()[0].subject_<<std::endl;
   Serializer::sendmessage(this->socketid_, msg );// ^^ ...OOP FTW xD
 }
 this->startrecieveing();
}
Session::~Session()
{
  //KILL THREADS
}
