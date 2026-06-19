#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>

class Server
{

public:
    Server();
private:
    int SetUpServerSocket();
    
};