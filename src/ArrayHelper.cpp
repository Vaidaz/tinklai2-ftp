#include "./ArrayHelper.h"

bool ArrayHelper::isInArray(string *array, int length, string elem){
  for( int i = 0; i < length; i++){
    if( elem.compare(array[i]) == 0 ){
      return true;
    }
  }

  return false;
}
