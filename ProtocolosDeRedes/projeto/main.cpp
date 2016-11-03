#include <iostream>
#include <winsock2.h>

using namespace std;

int main()
{
    //init
    int server_length;
    int port = 123;
    int STRLEN = 256;
    char recMessage[STRLEN];
    char sendMessage[STRLEN];
    char *sendMes = "SERVER READY\0";
    WSADATA wsaData;
    SOCKET mySocket;
    SOCKET myBackup;
    SOCKET acceptSocket;
    sockaddr_in myAddress;

    //create socket
    if( WSAStartup( MAKEWORD(2, 2), &wsaData ) != NO_ERROR )
    {
        cerr<<"Socket Initialization: Error with WSAStartup\n";
        system("pause");
        WSACleanup();
        exit(10);
    }

    mySocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mySocket == INVALID_SOCKET)
    {
        cerr<<"Socket Initialization: Error creating socket"<<endl;
        system("pause");
        WSACleanup();
        exit(11);
    }

    myBackup = mySocket;

    //bind
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( "0.0.0.0" );
    myAddress.sin_port = htons(port);

    if(bind(mySocket, (SOCKADDR*) &myAddress, sizeof(myAddress)) == SOCKET_ERROR)
    {
        cerr<<"ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
    }

    cout<<endl;
    while (1)
    {
        server_length = sizeof(struct sockaddr_in);
        recvfrom(mySocket, recMessage, STRLEN, 0, (SOCKADDR*) &myAddress, &server_length);
        cout<<recMessage<<endl;
        sendto(mySocket, sendMes , strlen(sendMes), 0, (SOCKADDR*) &myAddress, server_length);

    }

    return 0;
}