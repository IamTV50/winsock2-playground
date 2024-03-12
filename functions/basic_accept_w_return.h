#ifndef PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_W_RETURN_H
#define PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_W_RETURN_H

#endif //PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_W_RETURN_H

#include <iostream>
#include <winsock2.h> //add "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt
#include <ws2tcpip.h>
#include <cstring>

void basic_accept_w_return(){
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

    //create new socket for use of receiving and sending
    SOCKET clientSocket;
    wprintf(L"Waiting for client to connect...\n");

    //accepts the connection
    clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
    }
    wprintf(L"client connected... \n\n");

    //*
    //displaying received data  from client
    char buff[1024] = {0};
    recv(clientSocket, buff, sizeof(buff), 0);
    std::cout<<"received data: \n"<<buff<<"\n\n";
    //*/

    //send message back to postman
    std::string bodyMsg = "hello from server !@#123";
    std::string httpResponse = "HTTP/1.1 200 OK\n";
    httpResponse += "Content-Type: text/plain\n";
    httpResponse += "Content-Length: " + std::to_string(bodyMsg.length()) + "\n";
    httpResponse += "\n";  // Empty line to separate headers and body
    httpResponse += bodyMsg;

    iResult = send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    if(iResult == SOCKET_ERROR){
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
    }
    //std::cout<<"message \n"<<httpResponse<<" \nsent back to client...\n";
    std::cout<<"message sent back to client...\n";


    //closing sockets
    closesocket(listenSocket);
    closesocket(clientSocket);

    WSACleanup();
}
