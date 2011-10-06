#include "server.h"
#include "directory.h"
int main()
{
    Directory rootdir("");
    Server server(Server::IPv4, Server::TCP, 9000, rootdir);
    
    std::cout<<"Server started, waiting for incoming clients"<<std::endl;
    server.waitforincome();
    std::cout<<server._sout;
    return 0;
}