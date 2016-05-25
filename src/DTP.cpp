#include "./DTP.h"

DTP::DTP(){
};

DTP::~DTP(){
};

void DTP::sendMessage(string message){
  this->dtp.sendMessage(message + "\r\n");
};

bool DTP::hasPendingMessage(){
  return this->dtp.isPackage();
};

string DTP::receiveMessage(){
  this->response = this->dtp.receiveMessage();
  return this->response;
};

void DTP::setHost(string host){
  this->host = host;
};

void DTP::setPort(string port){
  this->port = port;
};


string DTP::getHost(){
  return this->host;
};

string DTP::getPort(){
  return this->port;
};

string DTP::getResponse(){
  return this->response;
};

void DTP::connect(string host, string port){
  this->host = host;
  this->port = port;

  this->dtp.setHost(host);
  this->dtp.setPort(port);
  this->dtp.connectToServer();
};

void DTP::disconect(){
  this->dtp.disconect();
}

string DTP::receiveList(){
  string list = "", line = "";

  if ( hasPendingMessage() ){
    do {
      line = receiveMessage();
      list += line;
    } while( hasPendingMessage() && line.length() > 0 );
  }
  return list;
};

void DTP::receiveFile(string path){
  if( hasPendingMessage() ){
    string response;
    ofstream file;

    file.open (path.c_str());
    do{
      response = receiveMessage();
      file << response;
    } while(hasPendingMessage() && response.length() > 0);
    file.close();
  }
};

void DTP::storeFile(string path){
  string line;
  ifstream file (path.c_str());
  if( file.is_open() ){
    while( getline (file, line) ){
      sendMessage(line);
    }
    file.close();
    disconect();
  }
};
