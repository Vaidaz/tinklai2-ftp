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
#include "./PI.h"
#include "./DTP.h"
#include "./PassiveResponseParser.h"

using namespace std;

class FTP{
  private:
    PI pi; // protocol interpreter
    string user;
    string password;
    string file_name;
    void setUp();
    void enterPassiveMode(DTP* dtp);
  public:
    FTP(string host, string port, string user, string password);
    void execute(string command);
    ~FTP();
};

#endif
