#include <iostream>

#include "./Settings.h"

using namespace std;

int main(){
  cout << Settings::val("ip") << endl;
  cout << Settings::val("user") << endl;
  cout << Settings::val("password") << endl;
  cout << Settings::val("port") << endl;
  return 0;
}