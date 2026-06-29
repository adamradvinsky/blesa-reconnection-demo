#include "../include/Client.h"
#define DEFAULT_PORT "27015"

std::vector<server> Client::savedServers;
std::string Client::name;
struct addrinfo Client::info;

Client::Client()
{
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = SetUpClientSocket();

    if (clientSocket != INVALID_SOCKET)
    {
        connectToServer(clientSocket, &info);
    }
}

void Client::setSocket(SOCKET newsocket)
{
    curSocket = newsocket;
}

SOCKET Client::getSocket()
{
    return curSocket;
}

SOCKET Client::SetUpClientSocket()
{
    printf("setting up client socket \n");
    int iResult;

    // set up into about this thingy
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    ptr = result;

    SOCKET ConnectSocket = INVALID_SOCKET;

    // create socket for client
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return INVALID_SOCKET;
    }
    else
    {
        printf("client socket has been opened \n");
        setSocket(ConnectSocket);
        return ConnectSocket;
    }
    return INVALID_SOCKET;
}

int Client::connectToServer(SOCKET socket, struct addrinfo *result)
{

    int iResult = 0;
    // connect socket
    iResult = connect(socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(socket);
        setSocket(INVALID_SOCKET);
        socket = INVALID_SOCKET;
        return -1;
    }

    freeaddrinfo(result);

    if (socket == INVALID_SOCKET)
    {
        printf("couldnt connect to server \n");
        WSACleanup();
        return -1;
    }
    else
    {
        printf("the sockets are connected !!!? \n");
        // send the info for the handshake

        return 0;
    }

    return -1;
}

int Client::sendHandShake()
{
    SOCKET socket = getSocket();

    char buffer[256];
    // recieve name
    memset(buffer, 0, 256);

    char *pname = name.data();
    int length = strlen(pname);

    // sending name
    int result = send(socket, pname, length, MSG_OOB);

    // recieving the servers name
    int iResult = recv(socket, buffer, 255, 0);

    result = checkSavedServers(buffer);

    if (result >= 0)
    {
        // server has been saved before
        printf("the server HAS been saved before \n");

        // std::string ltk = std::to_string(savedServers[result].LTK);
        // char *pltk = ltk.data();
        // printf("sending LTK - client \n");
        // result = send(socket, pltk, strlen(pltk), MSG_OOB);
    }
    else
    {
        // has not been saved
        printf("the server has not been saved before \n");

        // create new entry

    }

    return -1;

}

int Client::checkSavedServers(char *name)
{
    for (int i = 0; i < savedServers.size(); i++)
    {
        if (strcmp(savedServers[i].name.data(), name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void Client::sendMessage(char *message)
{
    SOCKET cSocket = getSocket();

    size_t strlen = std::strlen(message);

    int res = send(cSocket, message, strlen, MSG_OOB);
    if (res == 0)
    {
        printf("something didnt work it didnt send \n");
    }
    else
    {
        printf("sent over %d amount of bytes \n", res);
    }
}