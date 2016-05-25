// Protocol intepreter

#ifndef PI_H
#define PI_H

#include <iostream>

#include "./Socket.h"

using namespace std;

class PI{
  private:
    Socket pi;
    string response;
    string host;
    string port;
    void sendMessage(string message);
    bool hasPendingMessage();
  public:
    PI();
    ~PI();
    string receiveMessage();
    string getHost();
    string getPort();
    string getResponse();
    void setHost(string host);
    void setPort(string port);
    string connect(string host, string port);
    string commandUser(string user);
    string commandPassword(string password);
    string commandChangeWorkingDir(string path);
    string commandSetUTF8Encoding();
    string commandSetTypeAscii();
    string commandPrintWorkingDirectory();
    string commandDeleteFile(string path);
    string commandDeleteDir(string path);
    string commandMakeDir(string path);
    string commandHelp();
    string commandRestart();
    string commandEnterPassiveMode();
    string commandList();
    string commandRetrieve(string path);
    string commandNoop();
    void commandStore(string path);
};

#endif