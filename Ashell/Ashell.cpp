#include <fcntl.h>
#include <iostream> //remove this later
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <vector>
#include <sys/wait.h> //for waitpid(3)
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
void minipwd(){
  // Acts as the first thing pritned out, before parsing happens
  std::string path = get_current_dir_name();
  if (path.length() > 16){
    //Do the truncating
    //Find the first slash, going backwards
    std::string truncpath;
    std::size_t slashpos = path.rfind("/");

    truncpath = "/..." + path.substr(slashpos);
    AshellPrint(truncpath);
    AshellPrint("% ");
  }
  else{
    pwd();
  }
}
/*
	To Benjamin
	Here is how this function works
	You supply it the file descriptor of something
		If you dont have a FD, you're probably parsing a command first
		Use 1 as oldfd then
	then give it a filename.
	Then execute the command, and you should see the input accordingly

	If you're storing tokens in a vector, remember what I said in the CSIF
	You can iterate through that list till the index is to the second to last
	And call my fn on index, and index+1
	It should chain them all appropriatly.

	If you get any weirdness with executing things after that, it might this thing. I am unsure if it closes after use

	Sincerly
	Chase Maguire
	XOXOX
*/
int redir(int oldfd, const char* newfile){

	int newfd = open(newfile, O_CREAT|O_WRONLY|O_TRUNC);
	return dup2(newfd, oldfd);
}

//Not sure if this is overloading or accidental inclusion - Ben
int readir(std::string oldfile, const char*newfile){
  open(newfile, O_CREAT);

}


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
  std::cout << "\n"<<"Executing LS... "<< "No Directory"<<"\n";
  DIR* dir;
  struct dirent *entry;
  dir = opendir(get_current_dir_name());
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

std::vector<std::string> ff(const char* filename, const char* directory, const char* newdir){
	std::vector<std::string> vec;
  	DIR* dir;
  	struct dirent *entry;
  	struct stat statbuff;
	// Start by opening the directory that we're at, or attempting to
	if (NULL != newdir){
		chdir(newdir);
	}
	else {
		if (chdir(directory)==-1){
			AshellPrint("Error changing directory \n");
			return vec;
		}
	}
	//Open the directory
	dir = opendir(get_current_dir_name());
	//Start reading from it
	entry = readdir(dir);
	while (entry != NULL){ //So long as we have read something
		stat(entry->d_name, &statbuff);
		if (0==strcmp(filename, entry->d_name)){
			//Add it to vector?
			std::string slash = "/";
			std::string fileloc;
			if (newdir == NULL){
				fileloc = directory + slash + filename;
			}
			else{
				fileloc = directory + slash + newdir +slash + filename;
			}
			vec.push_back(fileloc);
			entry = readdir(dir);
		}
		else if ((0 == strcmp(".", entry->d_name)) ||(0 == strcmp("..", entry->d_name))){
			entry = readdir(dir); //Read the next entry
		}
		else if (S_ISDIR(statbuff.st_mode)){
			const char* saveddir = get_current_dir_name();
			if (chdir(entry->d_name)==-1){
				//Can't open the file
			}
			else{
				//Open it, and check what happens
				std::vector <std::string> retvec = ff(filename, directory, entry->d_name);
				for(int i=0; i<retvec.size(); ++i){
					vec.push_back(retvec[i]);
				}
			}
			chdir(saveddir);
			entry = readdir(dir);
		}
		else{
			entry = readdir(dir);
		}
	}

	// Should now be in the proper directory, or have returned by now
	return vec;
};

std::vector<std::string> ffemptdir(const char* filename, const char* newdir){
	//Should be very similair, except we need to change to whatever the local dir is
	std::vector<std::string> vec;
  	DIR* dir;
  	struct dirent *entry;
  	struct stat statbuff;
	// Start by opening the directory that we're at, or attempting to
	if (NULL != newdir){
		chdir(newdir);
	}
	//Open the directory
	dir = opendir(get_current_dir_name());
	//Start reading from it
	entry = readdir(dir);
	while (entry != NULL){ //So long as we have read something
		stat(entry->d_name, &statbuff);
		if (0==strcmp(filename, entry->d_name)){
			//Add it to vector?
			std::string slash = "/";
			std::string fileloc;
			if (newdir == NULL){
				fileloc = "." + slash + filename;
			}
			else{
				fileloc = "." + slash + newdir +slash + filename;
			}
			vec.push_back(fileloc);
			entry = readdir(dir);
		}
		else if ((0 == strcmp(".", entry->d_name)) ||(0 == strcmp("..", entry->d_name))){
			entry = readdir(dir); //Read the next entry
		}
		else if (S_ISDIR(statbuff.st_mode)){
			const char* saveddir = get_current_dir_name();
			if (chdir(entry->d_name)==-1){
				//Can't open the file
			}
			else{
				//Open it, and check what happens
				std::vector <std::string> retvec = ffemptdir(filename, entry->d_name);
				for(int i=0; i<retvec.size(); ++i){
					vec.push_back(retvec[i]);
				}
			}
			chdir(saveddir);
			entry = readdir(dir);
		}
		else{
			entry = readdir(dir);
		}
	}

	// Should now be in the proper directory, or have returned by now
	return vec;
};

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
int exec(char ** seperated){
        std::cout <<"In exec  "  <<"\n";
        pid_t pid;
        pid_t parent_pid;
        pid_t child_pid;
        pid_t wait;
        int status;
        std::cout <<"process ID pre fork:  "  << pid <<"\n";

        pid = fork(); //two process running

        //std::cout <<"process ID  "  << pid <<"\n";

        //child
        //http://man7.org/linux/man-pages/man2/getpid.2.html
        if(pid == -1){
                std::cout <<"fork error "  << pid <<"\n";
                //exit();
        }
        else if (pid == 0){
                //child process: exec
                std::cout <<"child process: " <<"\n";
                std::cout <<"child: "  << getpid() << " parent: "<< getppid()<<"\n";
                std::cout <<"exec: "  << execvp(seperated[0], seperated)<<"\n"; //if returns, error

                //getpid() returns PID of calling process
                //getppid() returns PID of the parent of the calling process (ID of parent, or ID of reparented)
        }
        else{
                //parent process: child executed, parent wait for child to finish
                std::cout <<"parent process: " <<"\n";
                std::cout <<"parent: "  << getpid() << " child: "<< pid<<"\n";
                waitpid(pid, &status, WEXITED);
                std::cout <<"child returned, status: "  << status << "\n";

        }

        //error

        //parent
                //wait for it to finish


}
void CallPrograms(char **seperated, int num_args){
    char * run_program = seperated[0]; //the first argument is the program to run

    if(run_program[0] == 'c' && run_program[1] == 'd' && run_program[2] == '\0'){
        std::cout <<"Execute CD "<<"\n";

        char * directory = seperated[1]; //TODO: check to see if it exists
        std::cout <<"directory "<< directory <<"\n";
        cd(directory);
    }
    else if(run_program[0] == 'l' && run_program[1] == 's' && run_program[2] == '\0'){

        if(num_args>0){ //fixes seg fault
            char * directory = seperated[1];
            //std::cout <<"Passing in:  "<< directory <<"\n";
            //char * directory;
            std::cout << "\n"<<"Executing LS... "<< "Directory: "<< directory<<"\n";
            ls(directory);
        }
        else{
            char * directory = get_current_dir_name();

            std::cout << "get dir " << get_current_dir_name()<< "\n";
            ls(); //IF NO ARGS, PASS IN NOTHING
        }

    }
    else if(run_program[0] == 'p' && run_program[1] == 'w' && run_program[2] == 'd' && run_program[3] == '\0'){
        std::cout <<"Execute PWD "<<"\n";
        pwd();
    }
    else if(run_program[0] == 'e' && run_program[1] == 'x' && run_program[2] == 'i' && run_program[3] == 't' && run_program[4] == '\0'){
        std::cout <<"Execute EXIT "<<"\n";
        exit();
    }
    else if(run_program[0] == 'f' && run_program[1] == 'f' && run_program[2] == '\0'){
        std::cout << "\n" << "Execute ff "<<"\n";
        char * filename = seperated[1];

        const char *file = "ff";
        const char *dir = "fftest";


        /*
        const char *file = "ff";
        const char *dir = "fftest";


        std::cout << "Chaning current dir " << get_current_dir_name()<< "\n";
        chdir(get_current_dir_name());
        std::vector<std::string> vec;
        vec = ffemptdir(file, NULL);
        for(int i=0; i<vec.size(); ++i){
          AshellPrint("Found locations in ");
          AshellPrint(vec[i]);
          AshellPrint("\n");
         }
         */
        //format:
        //std::vector<std::string> ff(const char* filename, const char* directory, const char* newdir)
        //std::vector<std::string> ffemptdir(const char* filename, const char* newdir){\


        //std::cout << "Chaning current dir " << get_current_dir_name()<< "\n";
        dir = get_current_dir_name();
        chdir(get_current_dir_name());
        std::vector<std::string> vec;



        //std::cout <<"Filename:  "<< filename << " Directory: " << dir << " New Dir: "<< "none"<<"\n";
        //vec = ffemptdir(file, NULL); //to make Directory and new Dir fftest
        //vec = ffemptdir(file, dir);
        const char *newdir = NULL; //likely seperate[1]
        std::cout <<"Filename:  "<< filename << " Directory: " << dir << " New Dir: "<< newdir <<"\n";
        vec = ff(filename, dir,  newdir);

        std::cout <<"ff vec size: "<< vec.size() <<"\n";
        for(int i=0; i<vec.size(); ++i){
          //AshellPrint("Found locations in ");
          AshellPrint(vec[i]);
          AshellPrint("\n");
        }
        //ff(filename, dir,  newdir);
    }
    else{
        std::cout <<"\n"<<"Run Exec(" << run_program<<");" <<"\n";
        exec(seperated);
    }


}

void parse(char *prog, char **parsed){




    //Parsing char array received, basically a split line function.
    //Currently seperates with ' ' TODO work with any character

    int i = 0;
    char split_memory[110];
    char * split = split_memory;
    char * seperated[15] = {0}; //initialize to zero or seg fault in ls call

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
    //TODO: fix tab


    std::string audible_bell = charString('\a'); //audible bell

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
        //TODO: ADJUST FOR MINIPWD ON BACKSPACE
        else if (arrow_flag && 0x5B != char_read){

            if(0x41 == char_read && num_lines != 0){
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
                        else if(0x41 == char_read && num_lines == 0){
                                //Audible bell up
                                AshellPrint(audible_bell);
                        }
            else if(0x42 == char_read && num_lines != num_lines_tot){
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
                        else if(0x42 == char_read && num_lines == num_lines_tot){
                                //Audible bell down
                                AshellPrint(audible_bell);
                        }
            else if(0x43 == char_read){
                //RIGHTARROW
                arrow_flag = false;
            }
            else if(0x44 == char_read){
                //LEFTARROW
                arrow_flag = false;
            }



        }
        else if (arrow_flag && 0x5B == char_read){
                        //Possibly an arrow key, set flag true and check next char above
            arrow_flag = true;
        }

                //BACKSPACE CASE *---
        else if (0x7F == char_read && num_chars > 0){
            AshellPrint("\b \b"); 	//outputs backspace
                        num_chars= num_chars - 2;
                        //std::cout <<"Passing in:  " <<"\n";

                        //std::cout<<num_chars; 					//corrects number of chars entered
            prog[num_chars] = char_read;	//replaces location in memory to backspace (maybe should be '\0'?)
        }
                else if (0x7F == char_read && num_chars <= 0){
                        AshellPrint(audible_bell);
                        num_chars--;
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
