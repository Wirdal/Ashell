#include <iostream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
void change(std::string directory){
    const char* cdirectory = directory.c_str();
    int err = chdir(cdirectory);
	if (-1 == err){
    	cout << "error" << "\n";
    }
};
int main (int argc, char *argv[]) {
	string path = "gibbersh";
	change(path);
	cout << get_current_dir_name() << "\n";
}