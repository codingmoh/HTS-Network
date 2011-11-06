#include <session.h>

Session::Session(int socketid, Directory userdir, Ldaplogin& ldap) :
      userdir_(userdir), socketid_(socketid), loggedin_(0), ldaplogin_(ldap)
{

}

void Session::start()
{
   /*this->sessionthread_ = new boost::thread(&Session::startrecieveing, this);
   sessionthread_->detach();*/
   startrecieveing();
}

void Session::startrecieveing()
{
   Serializer::receivemessage(this->socketid_, 20048);
}

void Session::executecommand(Message *& message)
{
   try
   {
      if (!loggedin_)
      {
         if (message->getmessagetype() == Message::mLogin)
         {

            Login * msg = dynamic_cast<Login*>(message);
            loggedin_ = this->ldaplogin_.loginuser(msg->user_, msg->password_);

            if (loggedin_ == true)
            {
               std::cout << "true" << std::endl;
               standard_messages sm(standard_messages::OK);
               Message * mes = &sm;
               Serializer::sendmessage(this->socketid_, mes);
            }

            else
            {
               std::cout << "false" << std::endl;
               standard_messages sm(standard_messages::ERR);
               Message * mes = &sm;
               Serializer::sendmessage(this->socketid_, mes);
            }
            delete message;
            this->startrecieveing();
         }
      }

      else
      {
         if (message->getmessagetype() != Message::mStandard)
         {

            if (message->getmessagetype() == Message::mMail)
            {
               this->userdir_.savemessage(*dynamic_cast<Mail*>(message));
               standard_messages sm(standard_messages::OK);
               Message * mes = &sm;
               Serializer::sendmessage(this->socketid_, mes);
            }

            else if (message->getmessagetype() == Message::mList)
            {
               Listmessage  lm = *dynamic_cast<Listmessage*>(message);
               this->userdir_.getmessages(lm);
	       
               Message * msg = new Listmessage(lm);
	       std::cout<<"size "<<lm.GetElements().size()<<std::endl;
               Serializer::sendmessage(this->socketid_, msg);// ^^ ...OOP FTW xD
	       delete msg;
            }

            else if (message->getmessagetype() == Message::mRead)
            {
               Read * msg = dynamic_cast<Read*>(message);
               Mail m = this->userdir_.getmessage(msg->user_, msg->number_);
               Message * msgret = &m;
               Serializer::sendmessage(this->socketid_, msgret);
            }


            else if (message->getmessagetype() == Message::mDelete)
            {
               Deletemessage * d_m = dynamic_cast<Deletemessage*>(message);
               this->userdir_.removemessage(d_m->user_, d_m->number_);
               standard_messages sm(standard_messages::OK);
               Message * mes = &sm;
               Serializer::sendmessage(this->socketid_, mes);

            }

            delete message;
            this->startrecieveing();
         }

         else if (message->getmessagetype() == Message::mStandard)
         {
            standard_messages * s_m = dynamic_cast<standard_messages*>(message);

            if (s_m->type_ == standard_messages::EXIT)
            {
               delete message;
               close(this->socketid_);
            }
         }
      }
   }

   catch (MessageException &e)
   {
      std::cout << "ERROR" << std::endl;
      Message * mes = &e;
      Serializer::sendmessage(this->socketid_, mes);
      delete message;
      this->startrecieveing();
   }
}

Session::~Session()
{
   //KILL THREADS
}
