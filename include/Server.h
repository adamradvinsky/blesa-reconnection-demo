#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>

struct client{

    std::string name;
    int LTK;

};

class Server
{

public:
    Server();
    static int LTK;

    // can only save 5 clients 
    static client savedClients[5];
private:
    SOCKET SetUpServerSocket();
    void ActiveServerSocket(SOCKET ListenSocket);
    void CreateConnection(SOCKET privateSocket);
    void PrivateServerConnectionEnCrypted(SOCKET privateSocket);
    void PrivateServerConnectionUnEnCrypted(SOCKET privateSocket);
    int GenerateLTK();
    bool checkSavedClients(char* name);
};