#ifndef FTP_H
#define FTP_H

#include <iostream>
#include <vector>

#include "./Socket.h"
#include "./StringUtils.h"

using namespace std;

class FTP{
  private:
    Socket pi; // protocol interpreter
    Socket dtp; // data transfer process
    string host;
    string port;
    string user;
    string password;
    void connect();
    void setUp();
  public:
    FTP(string host, string port, string user, string password);
    void sendMessage(string);
    Socket* getPI();
    Socket* getDTP();
    ~FTP();
};

#endif
