#ifndef FTP_H
#define FTP_H

#include <iostream>
#include <vector>
#include <dirent.h>

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
    string pi_response;
    string dtp_response;
    void connect();
    void setUp();
    void enterPassiveMode();
    void getdir(string dir, vector<string> *files);
  public:
    FTP(string host, string port, string user, string password);
    void sendMessage(string);
    Socket* getPI();
    Socket* getDTP();
    int execute(string command);
    int piHasPackage();
    int dtpHasPackage();
    string piReceiveMessage();
    string dtpReceiveMessage();
    bool requestedFileActionCompleted();
    ~FTP();
};

#endif
