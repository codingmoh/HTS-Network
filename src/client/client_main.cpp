#include <iostream>
#include <sstream>
#include <mail.h>

int main(int argc, char **argv) 
{
  Message * mg = new Mail();
  dynamic_cast<Mail*>(mg)->_msg ="hiiii";
  std::stringstream oss;
  boost::archive::text_oarchive oa(oss);
  oa << mg;
  
  Message * msg;
  boost::archive::text_iarchive ia(oss);
  ia >> msg;
  
  std::cout<<dynamic_cast<Mail*>(msg)->_msg<<std::endl;
}
