#ifndef PLAYING_WITH_WINSOCK2_URL_PARSE_H
#define PLAYING_WITH_WINSOCK2_URL_PARSE_H

#endif //PLAYING_WITH_WINSOCK2_URL_PARSE_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>

void small_receive_buffer_test(SOCKET clientSocket){
    int iResult = 0;
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
}
