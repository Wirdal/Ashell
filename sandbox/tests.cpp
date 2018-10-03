#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
void AshellPrint(const char* output){
//Write to 0 for STDIN_FILENO
//Write to 1 fir STDOUT_FILENO
//Write to 2 for STDERR_FILENO
//We're gonna write to 1, so we can print to the console
    //Find how much we need to write
	int size = strlen(output);
    int written = 0;
    while(size != written){
		int current = write(1, output, 1);
        written = written + current;
		output = output + current;
    };
};
int main (int argc, char *argv[]) {
	/* How to write to a file. generally
	 int fd;
	 const char path[10] = "tests.cpp";
	 fd = open(path ,O_WRONLY); //Opening for write only
	 std::cout << fd << "Hello!";
	*/
	// The main loop. Should just be reading inputs, then parsing after an enter
	// Needs to correclty deal with arrow keys and backspaces

	// This should be outputting whatever gets typed i
	AshellPrint("Test 1\n");
	AshellPrint("Test 2\n");
	AshellPrint("123\n");
	AshellPrint("file\\file2\\exe");

}