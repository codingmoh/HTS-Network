#include <iostream>
#include <sstream>
#include <mail.h>
#include <client.h>

int main(int argc, char **argv) 
{
  Client client(Client::IPv4,Client::TCP, 9000);
  
  
  client.connect_to_target("127.0.0.1");
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
