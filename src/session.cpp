#include <session.h>
#include <standard_messages.h>


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
}

void Session::executecommand(Message *& message)
{
 if(message->getmessagetype()==Message::mMail)
 {
   this->userdir_.savemessage(*dynamic_cast<Mail*>(message));
   this->startrecieveing();
 }
 else if(message->getmessagetype()==Message::mList)
 {
   Listmessage * lm = dynamic_cast<Listmessage*>(message);
   std::cout<<lm->GetUserName()<<std::endl;
   this->userdir_.getmessages(*lm);
   Message * msg = lm;
   std::cout<<lm->GetElements()[0].subject_<<std::endl;
   Serializer::sendmessage(this->socketid_, msg );// ^^ ...OOP FTW xD
   this->startrecieveing();
 }
 else if(message->getmessagetype()==Message::mStandard)
 {
    standard_messages * s_m = dynamic_cast<standard_messages*>(message);
    if(s_m->type_ == standard_messages::EXIT)
    {
      close(this->socketid_);
    }
 }
}
Session::~Session()
{
  //KILL THREADS
}
