#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>

class Client
{

public:
    Client();
    void setSocket(SOCKET socket);
    SOCKET getSocket();
    void sendMessage(char *message);
    int SetUpClientSocket();

private:
    SOCKET curSocket;

};