//Armin Mehr
//Auf Mohamed


#include "server.h"
#include "directory.h"
#include <signal.h>
#include <ldaplogin.h>
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <signal.h>


bool quit;
void exit_program(int)
{
  std::cout<<"bye";
  quit = true;
}
int main(int argc, char** argv)
{
  
   /*if (argc == 3)
   {*/
      Directory rootdir("ola"/*argv[2]*/);
      Ldaplogin l("ldap://ldap.technikum-wien.at","uid=if10b039,ou=people,dc=technikum-wien,dc=at", "anaahlashi", LDAP_VERSION3, "dc=technikum-wien,dc=at");
      
      signal(SIGINT,exit_program);

      
      Server server(Server::IPv4, Server::TCP, atoi("9000"/*argv[1]*/), rootdir, l);
      server.startlistening();
      std::cout << "Server started, waiting for incoming clients" << std::endl;
      while(true)
      {
	sleep(1);
	if(quit)
	{
	  std::cout<<"EXIT_CALLED"<<std::endl;
	  server.~Server();
	  break;
	}
      }
      return 0;
   }
   /*else
   {
     std::cout<<"Wrong usage"<<std::endl<<"Usage:"<<std::endl<<argv[0]<<" <PORT> <ROOTDIR>"<<std::endl;
   }
}*/
