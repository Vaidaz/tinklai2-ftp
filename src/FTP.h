#ifndef FTP_H
#define FTP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <ctype.h>
#include <algorithm>
#include <string>

#include "./Socket.h"
#include "./StringUtils.h"

using namespace std;

#define RETR 1
#define DEFAULT 2

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
    int passive_purpose;
    string file_name;
    void connect();
    void setUp();
    void enterPassiveMode(int purpose);
    void getdir(string dir, vector<string> *files);
    void retriveFile();
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
    void dtpHandleData();
    ~FTP();
};

#endif
