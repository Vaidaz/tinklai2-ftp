#include "./PassiveResponseParser.h"

PassiveResponseParser::PassiveResponseParser(){
};

PassiveResponseParser::PassiveResponseParser(string response){
  this->response = response;
};

PassiveResponseParser::~PassiveResponseParser(){
};

string PassiveResponseParser::getHost(){
  return this->host;
};
string PassiveResponseParser::getPort(){
  return this->port;
};
string PassiveResponseParser::getResponse(){
  return this->response;
};

void PassiveResponseParser::setResponse(string response){
  this->response = response;
};

void PassiveResponseParser::parse(){
  vector<string> parts1 = splitByDelimiter(this->response, '(');
  vector<string> parts2 = splitByDelimiter(parts1[1], ')');
  vector<string> parts3 = splitByDelimiter(parts2[0], ',');

  string listing_host = "";
  string listing_port = "";

  for(int i = 0; i < 4; i++){
    listing_host += parts3[i];
    if(i != 3) listing_host += ".";
  }

  listing_port = intToString( 256 * stringToInt(parts3[4]) + stringToInt(parts3[5]) );


  this->port = listing_port;
  this->host = listing_host;
}