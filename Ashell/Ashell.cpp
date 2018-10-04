// I/O services
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
void AshellPrint(std::string output){
    const char* output2 = output.c_str();
	AshellPrint(output2);
};
void AshellPrint(int output){
    std::string out2 = std::to_string(output);
    AshellPrint(out2);
};
void AshellPrint(const int* output){
    int size = sizeof(output);
    int written = 0;
    while(size != written){
        written = written - write(1, output, 1);
    }
};

size_t AshellRead(int fd, void *buf, size_t count){
//TODO
};

int AshellOpen(const char *path, int flags, .../*, mode_t mode*/){
//TODO
};
// Shell commands


char* pwd(){
//TODO
};

void exit(){
//TODO
};

void cd(char* directory){
//TODO
}; //Will need to deal with the HOME with a default var

char* ls(char* directory){
//TODO
};

char* ff(char* filename){
//TODO
};
