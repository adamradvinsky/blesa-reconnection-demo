#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>


int SetUpClientSocket();

void SendMessage(SOCKET socket); 