#include <iostream>

#include "./Settings.h"
#include "./Socket.h"
#include "./StdioHelper.h"

using namespace std;

int main(){
  string host = Settings::val("host");
  string port = Settings::val("port");
  string user = Settings::val("user");
  string password = Settings::val("password");

  cout << "sock.receiveMessage()" << endl;
  Socket sock(host, port);
  sock.connectToServer();
  // cout << sock.receiveMessage() << endl;

  cout << "USER" << endl;
  sock.sendMessage("USER " + user + "\n");
  cout << sock.receiveMessage() << endl;
  cout << "PASS" << endl;
  sock.sendMessage("PASS " + password + "\n");
  cout << sock.receiveMessage() << endl;
  cout << "PWD" << endl;
  sock.sendMessage("PWD\n");

  sock.sendMessage("MKD test\n");
  // cout << sock.receiveMessage() << endl;
  // cout << "TYPE I" << endl;
  // sock.sendMessage("TYPE I\n");
  // cout << sock.receiveMessage() << endl;
  // cout << "PORT" << endl;
  // sock.sendMessage("PORT 192,168,1,98,209,243\n");
  // cout << sock.receiveMessage() << endl;
  // cout << "LIST" << endl;
  // sock.sendMessage("LIST\n");
  // cout << sock.receiveMessage() << endl;

  // cout << sock.receiveMessage() << endl;

  int run = 1;
  string line;

  while(run){

    if(StdioHelper::isInput()){
      // cout << " Yra " << endl;
      getline (cin, line);
      cout << line << endl;
    }

    if(sock.isPackage()){
      cout << sock.receiveMessage() << endl;
    }

  }

  return 0;
}