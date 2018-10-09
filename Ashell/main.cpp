#include "Ashell.hh"
#include <unistd.h>
#include <string.h>
#include <iostream>

int main (int argc, char *argv[]) {
  const char *file = "ff";
  const char *dir = "Ashell/fftest";
  std::vector<char*> vec;
  ff(file, dir);
  for(int i=0; i<vec.size(); ++i){
    std::cout << vec[i] << "\n";
  }
  //Main loops goes here
  //While true
    //Wait for input
      //on input
      //Parse commands
        //do appropriate actions
        //return on input
 }
