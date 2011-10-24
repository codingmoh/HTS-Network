//Armin Mehr
//Auf Mohamed
#include "server.h"
#include "directory.h"
#include "ldaplogin.h"

int main(int argc, char** argv)
{
   if (argc == 3)
   {
      Directory rootdir(argv[2]);
      Ldaplogin l("ldap.technikum-wien.at", 389, "dc=technikum-wien,dc=at");
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
