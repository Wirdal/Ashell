#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <typeinfo>
#include <string>


using namespace std;
void AshellPrint(const char* output){
// As of now, we can only print out strings
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
	char* out;
	getcwd(out, 0);
}