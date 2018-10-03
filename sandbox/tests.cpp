#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main (int argc, char *argv[]) {
	/* How to write to a file. generally
	 int fd;
	 const char path[10] = "tests.cpp";
	 fd = open(path ,O_WRONLY); //Opening for write only
	 std::cout << fd << "Hello!";
	*/
	// The main loop. Should just be reading inputs, then parsing after an enter
	// Needs to correclty deal with arrow keys and backspaces

	// This should be outputting whatever gets typed in
	const char *input = "Hello Hello";
	std::string input;

}