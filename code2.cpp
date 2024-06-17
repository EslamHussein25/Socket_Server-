#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() 
{
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
     {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8099);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port 8081..." << std::endl;

        // Accept a client connection
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) 
        {
            std::cerr << "Error accepting connection" << std::endl;
            close(serverSocket);
            return 1;
        }

    while (true) 
    {

        // Handle the client connection
        char buffer[1024] = {0};
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            std::cerr << "Error reading from socket" << std::endl;
            close(clientSocket);
            continue;
        }

        std::cout << "Message from client: " << buffer << std::endl;

        // Echo the message back to the client
        int bytesSent = send(clientSocket, buffer, bytesRead, 0);
        if (bytesSent < 0) {
            std::cerr << "Error sending to socket" << std::endl;
        }

        // Close the client socket
       // close(clientSocket);
    }

    // Close the server socket (this line will never be reached in this example)
    close(serverSocket);
    return 0;
}