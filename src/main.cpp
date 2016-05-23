#include <iostream>
#include <string>
#include <unistd.h>

#include "./Settings.h"
#include "./Socket.h"
#include "./StdioHelper.h"
#include "./FTP.h"

using namespace std;

int main(){
  string host = Settings::val("host");
  string port = Settings::val("port");
  string user = Settings::val("user");
  string password = Settings::val("password");

  FTP ftp(host, port, user, password);

  bool run = true;
  string command;

  while(run){

    if( StdioHelper::isInput() ){
      getline (cin, command);
      ftp.execute(command);

      if( command.compare("q") == 0 ){
        run = false;
      }
    }

    if( ftp.piHasPackage() ){
      cout << ftp.piReceiveMessage();

      if( ftp.requestedFileActionCompleted() ){
        ftp.dtpHandleData();
      }
    }

  }

  return 0;
}
