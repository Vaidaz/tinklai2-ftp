#include <iostream>
#include <string>

#include "./Settings.h"
#include "./Socket.h"
#include "./StdioHelper.h"

using namespace std;

int main(){
  string host = Settings::val("host");
  string port = Settings::val("port");
  string user = Settings::val("user");
  string password = Settings::val("password");

  Socket sock(host, port);
  sock.connectToServer();

  sock.sendMessage("USER " + user + "\r\n");
  sock.receiveMessage();
  sock.sendMessage("PASS " + password + "\r\n");
  sock.receiveMessage();
  sock.sendMessage("CWD /shared\r\n");
  sock.receiveMessage();
  // 30023 = 256*117+71
  // where a1.a2.a3.a4 is the IP address and p1*256+p2 is the port number.

  sock.sendMessage("OPTS UTF8 ON\r\n");
  sock.receiveMessage();
  sock.sendMessage("TYPE A\r\n");
  sock.receiveMessage();
  sock.sendMessage("PASV\r\n");
  string response = sock.receiveMessage();

  vector<string> parts1 = StringUtils::splitByDelimiter(response, '(');
  vector<string> parts2 = StringUtils::splitByDelimiter(parts1[1], ')');
  vector<string> parts3 = StringUtils::splitByDelimiter(parts2[0], ',');

  string listing_host;
  string listing_port;

  for(int i = 0; i < 4; i++){
    listing_host += parts3[i];
    if(i != 3) listing_host += ".";
  }
  listing_port = StringUtils::intToString( 256 * StringUtils::stringToInt(parts3[4]) + StringUtils::stringToInt(parts3[5]) );

  Socket listening(listing_host, listing_port);
  listening.connectToServer();

  sock.sendMessage("LIST\r\n");

  cout << listening.receiveMessage() << endl;

  int run = 1;
  string line;

  // while(run){

  //   if( StdioHelper::isInput() ){
  //     getline (cin, line);
  //     // cout << line << endl;
  //   }

  //   if( sock.isPackage() ){
  //     cout << "Pirmas " + sock.receiveMessage() << endl;
  //   }

  //   if( listening.isPackage() ){
  //     cout << "Antras " + listening.receiveMessage() << endl;
  //   }

  // }

  return 0;
}