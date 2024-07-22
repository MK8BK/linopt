#include "mathutils.h"


unsigned long long mathutils::fact(int n){
  unsigned long long r{1};
  while(n>1){
    r *= n;
    n--;
  }
  return r;
}


