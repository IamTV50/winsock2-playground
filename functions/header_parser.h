#ifndef PLAYING_WITH_WINSOCK2_HEADER_PARSER_H
#define PLAYING_WITH_WINSOCK2_HEADER_PARSER_H

#endif //PLAYING_WITH_WINSOCK2_HEADER_PARSER_H

#include <iostream>
#include <string>
#include <regex>

std::string isolateHeaders(const std::string* wholeRequest){
    std::regex isolateHeadersRegex("(.*\\r\\n)+\\r\\n"); //gets only headers part of request without the body
    std::smatch matchData;
    std::string finnal = "";

    std::string tmp = *wholeRequest;
    std::regex_search(tmp, matchData, isolateHeadersRegex);

    for(auto match : matchData){
        finnal += match;
    }
    return finnal;
}

bool connectionKeepAlive(const std::string* headersData, const std::string header){
    std::regex keepAliveRegx("Connection: keep-alive"); //check if header Connection is set to keep-alive
    std::smatch aliveMatch;

    std::regex_search(*headersData, aliveMatch, keepAliveRegx);

    if(aliveMatch.empty()){ return false; }

    return true;
}