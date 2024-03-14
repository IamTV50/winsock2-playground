#ifndef PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_W_RETURN_H
#define PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_W_RETURN_H

#endif //PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_W_RETURN_H

#include <iostream>
#include <winsock2.h> //add "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt
#include <ws2tcpip.h>
#include <cstring>

void basic_accept_w_return(SOCKET clientSocket){
    int iResult = 0;

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
}
