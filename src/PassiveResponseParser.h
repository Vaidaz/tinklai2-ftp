#ifndef PASSIVE_RESPONSE_PARSER_H
#define PASSIVE_RESPONSE_PARSER_H

#include <iostream>
#include <vector>

#include "./Socket.h"
#include "./StringUtils.h"

using namespace std;
using namespace StringUtils;

class PassiveResponseParser{
  private:
    string host;
    string port;
    string response;
  public:
    PassiveResponseParser();
    PassiveResponseParser(string response);
    ~PassiveResponseParser();
    string getHost();
    string getPort();
    string getResponse();
    void setResponse(string response);
    void parse();
};

#endif