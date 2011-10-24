#include <session.h>
#include <standard_messages.h>
#include <deletemessage.h>

Session::Session(int socketid, Directory& userdir) :
      userdir_(userdir), socketid_(socketid)
{

}

void Session::start()
{
   /*  boost::thread sessionthread(&Session::startrecieveing, this);
   sessionthread.join();*/
   startrecieveing();
}

void Session::startrecieveing()
{
   Serializer::receivemessage(this->socketid_, 2048);
}

void Session::executecommand(Message *& message)
{
   try
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
            Message * msg = &lm;
            Serializer::sendmessage(this->socketid_, msg);// ^^ ...OOP FTW xD
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
