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
    //I can't think of a better way to do this
	AshellPrint(output.c_str());
};
void AshellPrint(int output){
    std::string out2 = std::to_string(output);
    AshellPrint(out2.c_str());
};


size_t AshellRead(int fd, void *buf, size_t count){
//TODO
};

int AshellOpen(const char *path, int flags, .../*, mode_t mode*/){
//TODO
};
// Shell commands


void pwd(){
	char *path = get_current_dir_name();
	AshellPrint(path);
	free(path);
	AshellPrint("\n");
};

void exit(){
    exit(EXIT_SUCCESS);
};

void cd(const char* directory){
    int err = chdir(directory);
    if (-1 == err){
     AshellPrint("Error changing directory \n");
    }
};
void cd(std::string directory){
    const char* cdirectory = directory.c_str();
    int err = chdir(cdirectory);
    if (-1 == err){
     AshellPrint("Error changing directory \n");

    }
};
char* ls(char* directory){
//TODO
};

char* ff(char* filename){
//TODO
};
