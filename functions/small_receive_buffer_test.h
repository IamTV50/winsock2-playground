#ifndef PLAYING_WITH_WINSOCK2_URL_PARSE_H
#define PLAYING_WITH_WINSOCK2_URL_PARSE_H

#endif //PLAYING_WITH_WINSOCK2_URL_PARSE_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>

//parse url and return code 200

void small_receive_buffer_test(){
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
        return;
    }

    //listen for incoming connection requests on created socket
    if(listen(listenSocket, SOMAXCONN) == SOCKET_ERROR){
        wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
        return;
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
        return;

    }
    wprintf(L"client connected... \n");

    std::vector<char> wholeMsg;
    char buff[100];

    do { // Receive until the peer closes the connection
        iResult = recv(clientSocket, buff, sizeof(buff), 0);

        if (iResult > 0 && iResult < sizeof(buff)){ // number of received bytes is smaller than buffer, so it's safe to assume that whole message was successfully read
            printf("Bytes received: %d\n", iResult);
            wholeMsg.insert(wholeMsg.cend(), buff, buff + iResult);
            break;
        }
        else if ( iResult > 0 ){
            printf("Bytes received: %d\n", iResult);
            wholeMsg.insert(wholeMsg.cend(), buff, buff + iResult);
        }
        else if ( iResult == 0 ){
            printf("Connection closed\n");
            break;
        }
        else{
            printf("recv failed: %d\n", WSAGetLastError());
            break;
        }
    } while(true);

    std::cout<<wholeMsg.size()<<" received data: \n\n";
    for(auto c : wholeMsg){ std::cout<<c; }
    std::cout<<"\n";

    std::string httpOkResponse = "HTTP/1.1 200 OK\n\n";

    iResult = send(clientSocket, httpOkResponse.c_str(), httpOkResponse.length(), 0);
    if(iResult == SOCKET_ERROR){
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
    }


    //closing sockets
    closesocket(listenSocket);
    closesocket(clientSocket);

    WSACleanup();
}
