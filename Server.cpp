#include <iostream>
#include <sys/socket.h> 
#include <unistd.h>
#include "netinet/in.h"

int main()
{
    //to open new socket on linux 
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
/*
    socketfd: It is the file descriptor for the socket.
    AF_INET: It specifies the IPv4 protocol family.
    SOCK_STREAM: It defines that the TCP type socket.
*/

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8063);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
/*
sockaddr_in: It is the data type that is used to store the address of the socket.
htons(): This function is used to convert the unsigned int from machine byte order to network byte order.
INADDR_ANY: It is used when we don’t want to bind our socket to any particular IP and instead make it listen to all the available IPs.
*/

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);


        char buffer[1024] = {0};
        std::string msg;
        std::string Teminate = "close"; // terminate the connection using this keyword 
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    std::cout<<"new client connected : "<<clientSocket<<"\n";

    while(true)
    {
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::string msg(buffer);
        std::cout << "Message from client found: " << msg<< std::endl;
      if(msg.find(Teminate) != std::string::npos)
      {
        close(clientSocket);
        close(serverSocket);
        break;
      }
    }












    return 0;
}