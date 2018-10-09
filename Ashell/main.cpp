#include "Ashell.hh"
#include <unistd.h>
#include <string.h>
#include <iostream>

int main (int argc, char *argv[]) {
  const char *file = "ff";
  const char *dir = "fftest";


  std::cout << "Chaning current dir " << get_current_dir_name()<< "\n";
  chdir(get_current_dir_name());
  std::vector<char*> vec;
  vec = ff(file, dir);
  for(int i=0; i<vec.size(); ++i){
    std::cout << "printing found locations " <<  vec[i] <<   "\n";
   }
  //Main loops goes here
  //While true
    //Wait for input
      //on input
      //Parse commands
        //do appropriate actions
        //return on input
 }
