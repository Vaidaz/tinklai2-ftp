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
  int counter = 0;

  while(run){
    counter++; // adds ~ every 0.1s

    if( counter >= 600 ){ // ~1min
      counter = 0;
      ftp.execute("NOOP");
    }

    if( StdioHelper::isInput() ){
      counter = 0;
      getline (cin, command);
      ftp.execute(command);

      if( command.compare("q") == 0 ){
        run = false;
      }
    }
  }

  return 0;
}
