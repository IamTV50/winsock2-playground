#ifndef PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_WO_RETURN_H
#define PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_WO_RETURN_H

#endif //PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_WO_RETURN_H

#include <iostream>
#include <winsock2.h> //add "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt
#include <ws2tcpip.h>

void basic_accept_wo_return(){
    WSADATA wsaData = {0};
    int iResult = 0;
    sockaddr_in service; // The socket address to be passed to bind

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET){
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );
    }

    //define sockaddr structure (https://learn.microsoft.com/en-us/windows/win32/winsock/sockaddr-2)
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(9999);

    //bind the socket
    iResult = bind(listenSocket, (SOCKADDR *) &service, sizeof(service));
    if (iResult == SOCKET_ERROR){
        wprintf(L"bind function failed with error = %d\n", WSAGetLastError() );
    }

    //listen for incoming connection requests on created socket
    if(listen(listenSocket, SOMAXCONN) == SOCKET_ERROR){
        wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
    }
    wprintf(L"listening on socket....\n");

    // Create a SOCKET for accepting incoming requests.
    SOCKET acceptSocket;
    wprintf(L"Waiting for client to connect...\n");

    //accepts the connection
    acceptSocket = accept(listenSocket, nullptr, nullptr);
    if (acceptSocket == INVALID_SOCKET) {
        wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
    }

    wprintf(L"client connected... \n");


    //closing sockets
    closesocket(listenSocket);
    closesocket(acceptSocket);

    WSACleanup();
}
