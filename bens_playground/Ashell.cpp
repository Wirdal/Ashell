#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//from noncanmode.c
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>

//from noncanmode.c
void ResetCanonicalMode(int fd, struct termios *savedattributes){
    tcsetattr(fd, TCSANOW, savedattributes);
}

//from noncanmode.c
void SetNonCanonicalMode(int fd, struct termios *savedattributes){
    struct termios TermAttributes;
    char *name;

    // Make sure stdin is a terminal.
    if(!isatty(fd)){
        fprintf (stderr, "Not a terminal.\n");
        exit(0);
    }

    // Save the terminal attributes so we can restore them later.
    tcgetattr(fd, savedattributes);

    // Set the funny terminal modes.
    tcgetattr (fd, &TermAttributes);
    TermAttributes.c_lflag &= ~(ICANON | ECHO); // Clear ICANON and ECHO.
    TermAttributes.c_cc[VMIN] = 1;
    TermAttributes.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSAFLUSH, &TermAttributes);
}
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
}

int AshellOpen(const char *path, int flags, .../*, mode_t mode*/){
//TODO
}
// Shell commands
/*

void pwd(){
	//char *path = get_current_dir_name();
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
// BIG help in ls
// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
void ls(const char* directory){
  DIR* dir;
  struct dirent *entry;
  dir = opendir(directory);
    if (NULL != dir){
	entry = readdir(dir);
	// Set the buffer for stat here
	struct stat statbuff; //I think segfaults happen here?
	while (NULL != entry){
		stat(entry->d_name, &statbuff);
		if (S_ISDIR(statbuff.st_mode)){
			AshellPrint("d");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IRUSR) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWUSR) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXUSR) {
			AshellPrint("x");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IRGRP) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWGRP) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXGRP) {
			AshellPrint("x");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IROTH) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWOTH) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXOTH) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		AshellPrint(" ");
		AshellPrint(entry->d_name);
		AshellPrint("\n");
		entry = readdir(dir);

	}
  }
};

void ls(std::string directory){
  DIR* dir;
  struct dirent *entry;
  dir = opendir(directory.c_str());
  if (NULL != dir){
	entry = readdir(dir);
	struct stat statbuff; //I think segfaults happen here?
	while (NULL != entry){
		stat(entry->d_name, &statbuff);
		if (S_ISDIR(statbuff.st_mode)){
			AshellPrint("d");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IRUSR) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWUSR) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXUSR) {
			AshellPrint("x");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IRGRP) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWGRP) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXGRP) {
			AshellPrint("x");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IROTH) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWOTH) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXOTH) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		AshellPrint(" ");
		AshellPrint(entry->d_name);
		AshellPrint("\n");
		entry = readdir(dir);

	}
  }
};

void ls(){
  DIR* dir;
  struct dirent *entry;
  //dir = opendir(get_current_dir_name());
  if (NULL != dir){
	entry = readdir(dir);
	// Set the buffer for stat here
	struct stat statbuff; //I think segfaults happen here?
	while (NULL != entry){
		stat(entry->d_name, &statbuff);
		if (S_ISDIR(statbuff.st_mode)){
			AshellPrint("d");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IRUSR) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWUSR) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXUSR) {
			AshellPrint("x");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IRGRP) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWGRP) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXGRP) {
			AshellPrint("x");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IROTH) {
			AshellPrint("r");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IWOTH) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		if (statbuff.st_mode & S_IXOTH) {
			AshellPrint("w");
		}
		else {
			AshellPrint("-");
		}
		AshellPrint(" ");
		AshellPrint(entry->d_name);
		AshellPrint("\n");
		entry = readdir(dir);

	}
  }
};

char* ff(char* filename){
//Might need to return a container or something
  DIR* dir;
  struct dirent *entry;
  //dir = opendir(get_current_dir_name());
  if (NULL != dir){
  entry = readdir(dir);
  struct stat statbuff;
    while (NULL != entry){
      // Check for directorys first
      stat(entry->d_name, &statbuff);
      if (S_ISDIR(statbuff.st_mode)){
          //chdir into that dir
          AshellPrint(ff(filename));
      }
      if (entry->d_name == filename){
        //the current directory
      }
    }
  }
  // Loop through each one of the files
  // If it is a directory
  //  chdir into it, and recurse on it
  // If it is a file
      // If it filename == looked for Filename
      // return that file. Since there can be only one
};
*/
//convert a string
//https://www.geeksforgeeks.org/how-to-convert-a-single-character-to-string-in-cpp/
std::string charString (char x){
    std::string str(1, x);
    return str;
}

int size_of(char *array){
    int i = 0;
    while(array[i] != '\0'){
        i++;
    }
    return i;
}


//Pass in an array of seperated commands to run
void CallPrograms(char **seperated, int num_args){
    char * run_program = seperated[0]; //the first argument is the program to run

    if(run_program[0] == 'c' && run_program[1] == 'd' && run_program[2] == '\0'){
        std::cout <<"Execute CD "<<"\n";

        char * directory = seperated[1]; //TODO: check to see if it exists
        std::cout <<"directory "<< directory <<"\n";
        //cd(directory);
    }
    else if(run_program[0] == 'l' && run_program[1] == 's' && run_program[2] == '\0'){

        if(num_args>0){ //fixes seg fault
            char * directory = seperated[1];
            //std::cout <<"Passing in:  "<< directory <<"\n";
            //char * directory;
            std::cout << "\n"<<"Executing LS... "<< "Directory: "<< directory<<"\n";
            //ls(directory);
        }
        else{
            std::cout << "\n"<<"Executing LS... "<< "No Directory"<<"\n";
            //ls(" "); //IF NO ARGS, PASS IN NOTHING
        }

    }
    else if(run_program[0] == 'p' && run_program[1] == 'w' && run_program[2] == 'd' && run_program[3] == '\0'){
        //std::cout <<"Execute PWD "<<"\n";
        //pwd();
    }
    else if(run_program[0] == 'e' && run_program[1] == 'x' && run_program[2] == 'i' && run_program[3] == 't' && run_program[4] == '\0'){
        std::cout <<"Execute EXIT "<<"\n";
        //exit();
    }
    else if(run_program[0] == 'f' && run_program[1] == 'f' && run_program[2] == '\0'){
        std::cout <<"Execute ff "<<"\n";
        char * filename = seperated[1];
        //std::cout <<"Filename:  "<< filename <<"\n";
        //ff(filename);
    }
    else{
        std::cout <<"\n"<<"Run Exec(" << run_program<<");" <<"\n";
        //TODO: exec(program_name)
    }


}

void parse(char *prog, char **parsed){
    //Parsing char array received, basically a split line function.
    //Currently seperates with ' ' TODO work with any character

    int i = 0;
    char split_memory[110];
    char * split = split_memory;
    char * seperated[15] = {0}; //initialize to zero or seg fault in ls call
    //std::cout <<"\n"<< seperated[1] <<"\n";

    //http://www.cplusplus.com/reference/cstring/strtok/
    split = strtok(prog, " ");

    while (split != NULL){
        seperated[i] = split;
        //std::cout <<"seperated[" << i << "] "<< seperated[i] << "\n";
        parsed[i] = split;
        //Not sure what split becomes
        split = strtok(NULL, " ");
        ++i;
    }
    seperated[i] = split;

    char * run_program = seperated[0];
    int num_args = i -1;


    CallPrograms(seperated, num_args);
}

void ReadAndParseCmd() {

    bool end_line = false;
    int max_size = 512;  	//TODO: switch to buffer or malloc system if necessary
    int num_chars = 0;		//the num of chars in a line
    int num_lines;
	int num_lines_tot;

    char test_array[100] = "12345678";

    size_t bytes_read = 0;

    
	//Setting up memory
    char prog_mem[100] = ""; //TODO: find max size
    char args_mem[100] = ""; //TODO: is this read-only memory
	

    char * prog = prog_mem; //Array containing chars until enter hit
    char *args = args_mem; 	//Input after the command/program
	//char * parsed; 			//to contain parsed input

    char hist[10][10];
	char char_read = '\0';


    bool arrow_flag;

    int max_bytes = 1; //reads at most 1 byte at a time

    //this may need to be STDIN_FILENO TODO
    int fd_read = 0; //this if the fd (file descriptor) for read


    struct termios SavedTermAttributes; //from noncanmode.c
    SetNonCanonicalMode(0, &SavedTermAttributes); //from noncanmode.c

    while (!end_line){

        int key_location = num_chars-1; //key location is the # of keys pressed in one line
        hist[num_lines_tot][key_location] = prog[key_location]; //sets history on each key press

        bytes_read = read(STDIN_FILENO, &char_read, max_bytes); //STDIN_FILENO may just be 1 TODO


        //EOT (end of transit) CASE *---
        if(0x04 == char_read){ // C-d 
            std::cout <<"its something else entirely..." << "\n";
            break;
        }
        
        //ARROW CASE *---
        else if (arrow_flag && 0x5B != char_read){

            if(0x41 == char_read){
                //UPARROW

				//Delete old command
                for(int n = 0; n < num_chars; n++){ 
                    AshellPrint("\b \b");
                }

				num_lines--;			//set line number
				prog = hist[num_lines];	//set program to history
                AshellPrint(prog);		//print program

                arrow_flag = false;		//out of arrow
            }
            else if(0x42 == char_read){
                //DOWNARROW

				//Delete old command
                for(int n = 0; n < num_chars; n++){ 
                    AshellPrint("\b \b"); 
                }

				num_lines++;			//set line number
				prog = hist[num_lines];	//set program to history
                AshellPrint(prog);		//print program

                arrow_flag = false;		//out of arrow
            }
            else if(0x43 == char_read){
                //RIGHTARROW
                arrow_flag = false;
            }
            else if(0x44 == char_read){
                //LEFTARROW
                arrow_flag = false;
            }
            else{
                //ERROR, shouldn't happen
            }


        }
        else if (arrow_flag && 0x5B == char_read){
			//Possibly an arrow key, set flag true and check next char above
            arrow_flag = true;
        }

		//BACKSPACE CASE *---
        else if (0x7F == char_read){
            AshellPrint("\b \b"); 	//outputs backspace
			num_chars--; 					//corrects number of chars entered
            prog[num_chars] = char_read;	//replaces location in memory to backspace (maybe should be '\0'?)
        }

        //STANDARD CASE (if the char can be printed) *---
        else if (isprint(char_read)){
            prog[num_chars] = char_read;					//sets location in memory to the printable char
            std::string str1 = charString(prog[num_chars]); //converts prog[i] to string so it can work with AshellPrint
            AshellPrint(str1);								//prints char to shell
        }
        //ENTER CASE *---
        else if (0x0A == char_read) {
			//exit the loop
            end_line = true;
        }
		//ARROW CASE	*---
        else{
			//Possibly an arrow key, set flag true and check next char above
            arrow_flag = true;
        }

        num_chars++; //while enter not pressed, read the next char


    }
    num_lines++;
	num_lines_tot++;	//keep track of total number of lines
    ResetCanonicalMode(STDIN_FILENO, &SavedTermAttributes); //reset canon mode
    parse(prog,&args); //Parse the program

}
