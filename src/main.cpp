#include <stdio.h>
#include <iostream>
#include <limits>
#include "../include/Server.h"
#include "../include/Client.h"

#define DEFAULT_PORT "27015"

#pragma comment(lib, "Ws2_32.lib")

int createServerSocket(char *ip);
int createClientSocket(char *ip);

int main(int argc, char **argv)
{

    std::cout << "Hello, Woddrld\n"
              << std::endl;

    WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0)
    {
        std::cout << "failed to initialize winsock" << std::endl;
        return 1;
    }
    else
    {
        printf("winsock has been initialized \n");
    }

    char input;

    printf("a: socket setup \nb: client setup \n");
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (input == 'a')
    {
        Server *server = new Server();
    }
    else
    {
        Client *client = new Client();
        printf("skibidi ! \n");
        char text[256];

        do
        {
            printf("send message: ");
            std::cin >> text;

            printf("going to try and send: %s \n", text);

            client->sendMessage(text);

        } while (text[0] != 'b');
    }

    std::cout << "press enter to exit ";
    std::cin.get();
    return 0;
}
