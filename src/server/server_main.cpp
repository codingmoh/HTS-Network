//Armin Mehr
//Auf Mohamed
#include "server.h"
#include "directory.h"
#include <signal.h>
#include <ldaplogin.h>
#include <boost/signal.hpp>
#include <boost/bind.hpp>

int main(int argc, char** argv)
{
  
   if (argc == 3)
   {
      Directory rootdir(argv[2]);
      Ldaplogin l("ldap://ldap.technikum-wien.at","uid=if...,ou=people,dc=technikum-wien,dc=at", "password", LDAP_VERSION3, "dc=technikum-wien,dc=at");
      
//       boost::signal0<void> sig;
//       sig.connect(boost::bind(&Ldaplogin::ldapUnbind, l));
//      sig();
      
      
      Server server(Server::IPv4, Server::TCP, atoi(argv[1]), rootdir, l);
      std::cout << "Server started, waiting for incoming clients" << std::endl;
      server.waitforincome();
      return 0;
   }
   else
   {
     std::cout<<"Wrong usage"<<std::endl<<"Usage:"<<std::endl<<argv[0]<<" <PORT> <ROOTDIR>"<<std::endl;
   }
}
