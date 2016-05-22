#include "./FTP.h"

// Public

FTP::FTP(string host, string port, string user, string password){
  this->host = host;
  this->port = port;
  this->user = user;
  this->password = password;

  connect();
  setUp();
};

void FTP::sendMessage(string message){
  this->pi.sendMessage(message + "\r\n");
}

FTP::~FTP(){

};

Socket* FTP::getPI(){
  return &this->pi;
};

Socket* FTP::getDTP(){
  return &this->dtp;
};

int FTP::execute(string command){
  const string message_commands[] = {
    "PWD"
  };

  for( int i = 0; i < sizeof(message_commands)/sizeof(message_commands[0]); i++){
    if( command.compare(message_commands[i]) == 0 ){
      sendMessage(command);
      return 0;
    }
  }

  if( command.compare("LIST") == 0 ){
    enterPassiveMode();
    sendMessage(command);
    return 0;
  }

  return 1;
}

// Private

void FTP::connect(){
  this->pi.setHost(this->host);
  this->pi.setPort(this->port);
  this->pi.connectToServer();
};

void FTP::setUp(){
  cout << "****************** Setting up ****************" << endl;
  sendMessage("USER " + user);
  cout << this->pi.receiveMessage();
  sendMessage("PASS " + password);
  cout << this->pi.receiveMessage();
  sendMessage("CWD /shared\r\n");
  cout << this->pi.receiveMessage();

  sendMessage("OPTS UTF8 ON");
  cout << this->pi.receiveMessage();
  sendMessage("TYPE A");
  cout << this->pi.receiveMessage();

  cout << "************** End of Setting up *************" << endl;
  cout << endl;
};

void FTP::enterPassiveMode(){
  sendMessage("PASV");
  string response = this->pi.receiveMessage();
  cout << response;

  vector<string> parts1 = StringUtils::splitByDelimiter(response, '(');
  vector<string> parts2 = StringUtils::splitByDelimiter(parts1[1], ')');
  vector<string> parts3 = StringUtils::splitByDelimiter(parts2[0], ',');

  string listing_host = "";
  string listing_port = "";

  for(int i = 0; i < 4; i++){
    listing_host += parts3[i];
    if(i != 3) listing_host += ".";
  }

  listing_port = StringUtils::intToString( 256 * StringUtils::stringToInt(parts3[4]) + StringUtils::stringToInt(parts3[5]) );

  this->dtp.disconect();
  this->dtp.setHost(listing_host);
  this->dtp.setPort(listing_port);
  this->dtp.connectToServer();
};

int FTP::piHasPackage(){
  return this->pi.isPackage();
};

int FTP::dtpHasPackage(){
  return this->dtp.isPackage();
};

string FTP::piReceiveMessage(){
  this->pi_response = this->pi.receiveMessage();
  return pi_response;
};

string FTP::dtpReceiveMessage(){
  this->dtp_response = this->dtp.receiveMessage();
  return this->dtp_response;
};

bool FTP::requestedFileActionCompleted(){
  vector<string> lines = StringUtils::splitByDelimiter(this->pi_response, '\n');

  for(int i=0; i < lines.size(); i++){
    string response_code = StringUtils::splitByDelimiter(lines[i], ' ')[0];

    if(response_code.compare("226") == 0){
      return true;
    }
  }

  return false;
};
