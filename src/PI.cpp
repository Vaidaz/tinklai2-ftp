#include "./PI.h"

PI::PI(){
};

PI::~PI(){
};

void PI::sendMessage(string message){
  this->pi.sendMessage(message + "\r\n");
};

bool PI::hasPendingMessage(){
  return this->pi.isPackage();
};

string PI::receiveMessage(){
  this->response = this->pi.receiveMessage();
  return this->response;
};

void PI::setHost(string host){
  this->host = host;
};

void PI::setPort(string port){
  this->port = port;
};


string PI::getHost(){
  return this->host;
};

string PI::getPort(){
  return this->port;
};

string PI::getResponse(){
  return this->response;
};

string PI::connect(string host, string port){
  this->host = host;
  this->port = port;

  this->pi.setHost(host);
  this->pi.setPort(port);
  this->pi.connectToServer();
  return receiveMessage();
};

string PI::commandUser(string user){
  sendMessage("USER " + user);
  return receiveMessage();
}

string PI::commandPassword(string password){
  sendMessage("PASS " + password);
  return receiveMessage();
}

string PI::commandChangeWorkingDir(string path){
  sendMessage("CWD " + path);
  return receiveMessage();
};

string PI::commandSetUTF8Encoding(){
  sendMessage("OPTS UTF8 ON");
  return receiveMessage();
};

string PI::commandSetTypeAscii(){
  sendMessage("TYPE A");
  return receiveMessage();
};

string PI::commandPrintWorkingDirectory(){
  sendMessage("PWD");
  return receiveMessage();
};

string PI::commandDeleteFile(string path){
  sendMessage("DELE " + path);
  return receiveMessage();
};

string PI::commandDeleteDir(string path){
  sendMessage("RMD " + path);
  return receiveMessage();
};

string PI::commandMakeDir(string path){
  sendMessage("MKD " + path);
  return receiveMessage();
};

string PI::commandHelp(){
  sendMessage("HELP");
  return receiveMessage() + receiveMessage(); // TODO: fix
};

string PI::commandRestart(){
  sendMessage("REST");
  return receiveMessage();
};

string PI::commandEnterPassiveMode(){
  sendMessage("PASV");
  return receiveMessage();
}

string PI::commandList(){
  sendMessage("LIST");
  return receiveMessage() + receiveMessage(); // TODO: fix
};

string PI::commandRetrieve(string path){
  sendMessage("RETR " + path);
  return receiveMessage() + receiveMessage(); // TODO: fix
}

string PI::commandNoop(){
  sendMessage("NOOP");
  return receiveMessage();
};

void PI::commandStore(string path){
  sendMessage("STOR " + path);
}
