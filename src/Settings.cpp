#include "./Settings.h"

string Settings::val(string searched_key){
  string line;
  ifstream settings_file(FILE_PATH);
  if (settings_file.is_open()){
    vector<string> pairs;

    while ( getline (settings_file, line) ){
      pairs = StringUtils::splitByDelimiter(line, ':');

      if( searched_key.compare(pairs[0]) == 0 ) {
        return pairs[1];
      }

    }

    settings_file.close();

  } else {
    cout << "Unable to open file" << endl;
  }

  return "error";
}