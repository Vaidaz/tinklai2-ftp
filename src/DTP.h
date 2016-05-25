// Data transfer process

#ifndef DTP_H
#define DTP_H

#include <iostream>
#include <fstream>

#include "./Socket.h"

using namespace std;

class DTP{
  private:
    Socket dtp;
    string host;
    string port;
    string response;
    void sendMessage(string message);
    bool hasPendingMessage();
    string receiveMessage();
  public:
    DTP();
    ~DTP();
    string getHost();
    string getPort();
    string getResponse();
    void setHost(string host);
    void setPort(string port);
    void connect(string host, string port);
    void parsePasiveResponse(string response);
    string receiveList();
    void receiveFile(string path);
    void storeFile(string path);
    void disconect();
};

#endif