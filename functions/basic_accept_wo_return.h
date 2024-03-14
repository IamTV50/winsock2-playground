#ifndef PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_WO_RETURN_H
#define PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_WO_RETURN_H

#endif //PLAYING_WITH_WINSOCK2_BASIC_ACCEPT_WO_RETURN_H

#include <iostream>
#include <winsock2.h> //add "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt
#include <ws2tcpip.h>

void basic_accept_wo_return(SOCKET clientSocket){
    //displaying received data  from client
    char buff[1024] = {0};
    recv(clientSocket, buff, sizeof(buff), 0);
    std::cout<<"received data: "<<buff<<std::endl;
}
