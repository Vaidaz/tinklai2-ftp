#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "./StringUtils.h"

using namespace std;

#define FILE_PATH "settings.txt"

namespace Settings{
  string val(string str);
};

#endif