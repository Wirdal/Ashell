#include "Ashell.hh"
#include <unistd.h>
#include <string.h>
#include <iostream>

int main (int argc, char *argv[]) {

  minipwd();
  while(1){
    ReadAndParseCmd();
    //minipwd();
  }

 }
