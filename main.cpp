#include <iostream>
#include "functions/basic_accept_wo_return.h"
#include "functions/basic_accept_w_return.h"
#include "functions/small_receive_buffer_test.h"
#include "functions/send_html.h"

int main() {
    WSADATA wsaData = {0};
    int iResult = 0;
    sockaddr_in service; // The socket address to be passed to bind

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET){
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );
        return -1;
    }

    //define sockaddr structure (https://learn.microsoft.com/en-us/windows/win32/winsock/sockaddr-2)
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(9999);

    //bind the socket
    iResult = bind(listenSocket, (SOCKADDR *) &service, sizeof(service));
    if (iResult == SOCKET_ERROR){
        wprintf(L"bind function failed with error = %d\n", WSAGetLastError() );
        return -1;
    }

    //listen for incoming connection requests on created socket
    if(listen(listenSocket, SOMAXCONN) == SOCKET_ERROR){
        wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
        return -1;
    }
    wprintf(L"listening on socket....\n");

    //create new socket for use of receiving and sending
    SOCKET clientSocket;
    wprintf(L"Waiting for client to connect...\n");

    //accepts the connection
    clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
        closesocket(listenSocket);
        closesocket(clientSocket);
        WSACleanup();
        return -1;

    }
    wprintf(L"client connected... \n");


    //basic_accept_wo_return(clientSocket);
    //basic_accept_w_return(clientSocket);
    //small_receive_buffer_test(clientSocket);
    send_html(clientSocket);


    //closing sockets
    closesocket(listenSocket);
    closesocket(clientSocket);

    WSACleanup();

    return 0;
}
