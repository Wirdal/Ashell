#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
void ls(){
  DIR* dir;
  struct dirent *entry;
  dir = opendir(get_current_dir_name());
  if (NULL != dir){
	entry = readdir(dir);
	// Set the buffer for stat here
	struct stat *statbuff; //I think segfaults happen here?
	while (NULL != entry){
		stat(entry->d_name, statbuff);
		__mode_t modes= statbuff->st_mode;
		std::cout << modes << "\n";
		printf(entry->d_name);
		printf("\n");
		entry = readdir(dir);

	}
  }
};
int main (int argc, char *argv[]) {
	ls()
}