#include "./StringUtils.h"

vector<string> StringUtils::splitBySpaces(string message){
  string word;
  stringstream ss(message);

  vector<string> words;

  while (ss >> word){
    words.push_back(word);
  }

  return words;
};

vector<string> StringUtils::splitByComma(string str){
  char ch;
  vector<string> parts;
  string part = "";
  for(int i = 0; i < str.size(); i++){
    ch = str[i];
    if(ch == ','){
      parts.push_back(part);
      part = "";
    } else {
      part += ch;
    }
  }

  if(!part.empty()){
    parts.push_back(part);
  }

  return parts;
};

string StringUtils::removeCrLf(string str){
  string new_str = "";
  char ch;
  int length = str.size();
  int cr_place = length - 1;
  int lf_place = length;
  for(int i = 0; i < length; i++){
    ch = str[i];
    if( (i != cr_place || ch != '\r') && (i != lf_place || ch != '\n') ){
      new_str += ch;
    }
  }
  return new_str;
};

string StringUtils::cutUntillNewLine(string message){
  string msg;
  for(int i = 0; i < message.length() - 1; i++){
    if(message[i] == '\r' || message[i] == '\n'){
      break;
    }

    msg += message[i];
  }

  return msg;
};

vector<string> StringUtils::splitByDelimiter(string str, char delimiter){
  char ch;
  vector<string> parts;
  string part = "";
  for(int i = 0; i < str.size(); i++){
    ch = str[i];
    if(ch == delimiter){
      parts.push_back(part);
      part = "";
    } else {
      part += ch;
    }
  }

  if(!part.empty()){
    parts.push_back(part);
  }

  return parts;
}

string StringUtils::intToString(int number){
  ostringstream ss;
  ss << number;
  return ss.str();
}

int StringUtils::stringToInt(string str){
  return atoi(str.c_str());
}
