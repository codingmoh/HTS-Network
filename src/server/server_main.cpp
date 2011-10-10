//Armin Mehr
//Auf Mohamed
#include "server.h"
#include "directory.h"

int main(int argc, char** argv)
{
   if (argc == 3)
   {
      Directory rootdir(argv[2]);
      Server server(Server::IPv4, Server::TCP, atoi(argv[1]), rootdir);
      std::cout << "Server started, waiting for incoming clients" << std::endl;
      server.waitforincome();
      return 0;
   }
   else
   {
     std::cout<<"Wrong usage"<<std::endl<<"Usage:"<<std::endl<<argv[0]<<" <PORT> <ROOTDIR>"<<std::endl;
   }
}