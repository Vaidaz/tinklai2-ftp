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

  int run = 1;
  string line = "";
  string response = "";
  bool ok = false;

  vector<string> parts;
  vector<string> parts2;

  Socket* pi = ftp.getPI();
  Socket* dtp = ftp.getDTP();

  ftp.sendMessage("LIST");

  while(run){

    if( StdioHelper::isInput() ){
      getline (cin, line);
      // cout << line << endl;
    }

    if( pi->isPackage() ){
      response = "";
      response = pi->receiveMessage();
      cout << response << endl;
      parts = StringUtils::splitByDelimiter(response, '\n');

      ok = false;
      for(int i=0; i < parts.size(); i++){
        parts2 = StringUtils::splitByDelimiter(parts[i], ' ');

        if(parts2[0].compare("226") == 0){
          ok = true;
        }
      }

      if(ok){
        cout << dtp->receiveMessage() << endl;
      }
    }

  }

  return 0;
}
