#include "Ashell.hh"
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]) {
  std::string dir ="/";
  ls(dir);
  ReadAndParseCmd(); //eventually this will be main loop initiator: like while(ReadAndParseCmd()) [see pg 112 of text]
  //Main loops goes here
  //While true
    //Wait for input
      //on input
      //Parse commands
        //do appropriate actions
        //return on input
 }
