#include <server.h>

int main()
{
    Server server(Server::IPv4, Server::TCP, 9000);
    std::cout<<"Server started, waiting for incoming clients"<<std::endl;
    server.waitforincome();
    std::cout<<server._sout;
}