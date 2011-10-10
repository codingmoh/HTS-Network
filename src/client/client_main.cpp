#include <iostream>
#include <sstream>
#include "mail.h"
#include "client.h"
#include <listmessage.h>

static void getrestrictedlength(std::string name, std::string& input, int size)
{
   while (input.size() > size || input.size() < 1)
   {
      std::cout << name;
      std::getline(std::cin, input);
   }
}

int main(int argc, char **argv)
{
   std::string name = "hhu";
   std::cout << "Please enter your username:" << std::endl;
   //std::cin>>name;
   Client client(Client::IPv4, Client::TCP, 9000, name);

   if (client.connect_to_target("127.0.0.1"))
   {
      std::cout << "Successfully connected" << std::endl;
   }

   else
   {
      std::cout << "Connection ERROR" << std::endl;
      exit(1);
   }

   std::string command;

   while (command != "EXIT")
   {
      //command = "SEND";
      std::cout << "Enter Command:" << std::endl;
      std::cin>>command;

      if (command == "SEND")
      {
         std::string from, to, subject;
         getrestrictedlength("From:", from, 8);
         getrestrictedlength("To:", to, 8);
         getrestrictedlength("Subject:", subject, 8);

         std::cout << std::endl << "Message: (The delim char is '.')";
	 char message[256];
         std::cin.getline(message,256,'.');

         Message * m = new Mail(to, from, subject, message);

         client.sendmessage(m);

         delete m;
      }
      else if(command == "LIST")
      {
	std::string user;
	getrestrictedlength("Username:",user,8);
	std::cout<<"here"<<std::endl;
	Message * mes = new Listmessage(user);
	std::cout<<"after new"<<std::endl;
	client.sendmessage(mes);
	std::cout<<"after send"<<std::endl;
	client.waitresponse();
	std::cout<<"after wait"<<std::endl;
	delete mes;
	std::cout<<"after del"<<std::endl;
      }
   }

   /*
   Message * mg = new Mail();
   dynamic_cast<Mail*>(mg)->_msg ="hiiii";
   std::stringstream oss;
   boost::archive::text_oarchive oa(oss);
   oa << mg;

   Message * msg;
   boost::archive::text_iarchive ia(oss);
   ia >> msg;

   switch(msg->getmessagetype())
   {
     case Message::mMail:
       std::cout<< dynamic_cast<Mail*>(msg)->_msg<<std::endl;
       break;
       /*case LIST
        * case exit
        * ....usw

   }*/
}
