#ifndef PLAYING_WITH_WINSOCK2_SMALL_SEND_BUFFER_TEST_H
#define PLAYING_WITH_WINSOCK2_SMALL_SEND_BUFFER_TEST_H

#endif //PLAYING_WITH_WINSOCK2_SMALL_SEND_BUFFER_TEST_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <string>

std::string readHtml(const std::string file){
    std::ifstream htmlFile;
    std::string line = "";
    std::string htmlContents = "";

    htmlFile.open(file);

    if(!htmlFile.is_open()){
        std::string errMsg = "error opening/reading file";

        std::string errResponse = "HTTP/1.1 500\n";
        errResponse += "Content-Type: text/html; charset=utf-8;\n";
        errResponse += "Content-Length: " + std::to_string(errMsg.length()) + "\n";
        errResponse += "\n";
        errResponse += errMsg;

        return errResponse;
    }

    while(std::getline(htmlFile, line)){
        htmlContents += line + "\n";
    }

    htmlFile.close();
    //std::cout<<htmlContents<<"\n";

    std::string okResponse = "HTTP/1.1 200 OK\n";
    okResponse += "Content-type: text/html; charset=utf-8;\n";
    okResponse += "Content-length: " + std::to_string(htmlContents.length()) + "\n";
    okResponse += "\n";
    okResponse += htmlContents;

    return okResponse;
}

void send_html(SOCKET clientSocket){
    int iResult = 0;
    char recvBuff[1024] = {0};
    recv(clientSocket, recvBuff, sizeof(recvBuff), 0);

    //std::string httpResponse = readHtml("../html/hello.html");
    std::string httpResponse = readHtml("../html/big.html");

    //std::cout<<httpResponse<<std::endl;

    iResult = send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    if(iResult == SOCKET_ERROR){
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
    }
}