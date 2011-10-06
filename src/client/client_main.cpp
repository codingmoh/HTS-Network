#include <iostream>
#include <sstream>
#include "mail.h"
#include "client.h"

int main(int argc, char **argv) 
{
  std::string name;
  std::cout<<"Please enter your username:"<<std::endl;
  std::cin>>name;
  Client client(Client::IPv4,Client::TCP, 9000, name);
  
  if(client.connect_to_target("127.0.0.1"))
  {
      std::cout<<"Successfully connected"<<std::endl;
  }
  else
  {
      std::cout<<"Connection ERROR"<<std::endl;
      exit(1);
  }
  
  std::string command;
  while (command != "EXIT")
  {
    command ="";
    std::cout<<"Enter Command:"<<std::endl;
    std::cin>>command;
    
    if(command == "SEND")
    {
        std::string from, to, subject, message;
	std::cout<<"From:";
	std::cin>>from;
	std::cout<<std::endl<<"To:";
	std::cin>>to;
	std::cout<<std::endl<<"Subject:";
	std::cin>>subject;
	std::cout<<std::endl<<"Message:";
	std::cin>>message;
	Message * m = new Mail(to,from,subject,message);	
	client.sendmessage(m);
	delete m;
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
