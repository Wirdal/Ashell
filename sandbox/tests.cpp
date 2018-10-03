#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
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
	char input;
	while (1){
		read(0, &input, 1); 
		if (isprint(input)){ //We read one byte at a time
			std::cout << "This is what comes out " << input << "\n";
		}
		else if ("0\\") { //The end of a string will be this thing
			std::cout << "Nothing left \n"; //As in, when it reads, this is the end
		}
	}
}