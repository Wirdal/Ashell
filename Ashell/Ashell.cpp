#include <fcntl.h>
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
                AshellPrint("\nError changing directory \n");
        }
        else{
            AshellPrint("\n");
        }
};
void cd(std::string directory){
        const char* cdirectory = directory.c_str();
        int err = chdir(cdirectory);
        if (-1 == err){
                AshellPrint("\nError changing directory \n");

        }
        else{
            AshellPrint("\n");
        }
};


// BIG help in ls
// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
void ls(const char* directory){
  AshellPrint("\n");
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
  AshellPrint("\n");
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
    AshellPrint("\n");
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
int exec(char ** seperated, int * metadata, char * tokens){
                pid_t pid;
                pid_t parent_pid;
                pid_t child_pid;
                pid_t wait;
                int status;
                int num_children = 0;
                int num_numparents = 0;
                int fd_old;
                int fd[2];
                int WRITE_END = 1;
                int READ_END = 0;
                bool used_output = false;
                bool used_input = false;

                int num_seperated = metadata[0];


                //METADATA
                //0 - num splits, 1 - num args, 2 - num pipes, 3 - num right, 4 - num left, 5 - num spaces
                metadata[1] = metadata[0] + 1;
                int num_args = metadata[1] + 1; // this has to be +1

\

                //For each argument
                for(int i = 0; i < num_args; i++){

                        int input;
                        int output;

                        //https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
                        //FORK
                        pipe(fd);
                        pid = fork(); //two process running
                        num_children++;
                        fd_old = 0;
                        //std::cout <<"process ID  "  << pid <<"\n";

                        //child
                        //http://man7.org/linux/man-pages/man2/getpid.2.html
                        if(pid == -1){
                            exit();
                        }
                        else if (pid == 0){
                                        //child process: exec

                                        //getpid() returns PID of calling process
                                        //getppid() returns PID of the parent of the calling process (ID of parent, or ID of reparented)

                                        //https://www.geeksforgeeks.org/dup-dup2-linux-system-call/

                                        //redirect right: https://unix.stackexchange.com/questions/122977/what-is-the-correct-name-for-the-command
                                        dup2(fd_old, 0); //old fd and new fd, new fd dup2 creates a copy, old fd in

                                        //chaining commands with chase's fn
                                        //i+1 is the next command
                                        if(i + 1 < num_args && tokens[i] == '>'){

                                                const char* newfile = seperated[i + 1];


                                                //return dup2(newfd, oldfd);
                                                output = redir(0, newfile); //old fd, newfile
                                                used_output = true;
                                        }
                                        if(i + 1 < num_args && tokens[i] == '<'){
                                                const char* newfile = seperated[i + 1];
                                                //return dup2(newfd, oldfd);
                                                input = redir(0, newfile); //old fd, newfile
                                                //check if input == -1
                                                used_input = true;
                                        }
                                        if(i + 2 < num_args && tokens[i + 1] == '>'){

                                                const char* newfile = seperated[i + 2];
                                                output = redir(0, newfile); //old fd, newfile
                                                //check if input == -1
                                                used_output = true;
                                        }


                                if(num_children != num_args){
                                        //if its not a leaf child: output the childs output to STDOUT
                                        //https://stackoverflow.com/questions/40565197/pipe-usage-in-c


                                        //https://stackoverflow.com/questions/12902627/the-difference-between-stdout-and-stdout-fileno-in-linux-c
                                        //Helpful: https://stackoverflow.com/questions/25722730/cannot-dup2-write-end-of-a-pipe-to-stdout
                                        dup2(fd[WRITE_END], STDOUT_FILENO);
                                        if(used_input){

                                                dup2(input, STDIN_FILENO);
                                                close(input);
                                        }
                                        if(used_output){

                                                dup2(output, STDOUT_FILENO);
                                                close(output);
                                        }

                                }
                                else{
                                        //if its the last child: replace STDOUT with file
                                        if(used_input){
                                                //input = redir(STDIN_FILENO, input) //not sure if we need to redirect, may just need to dup

                                                dup2(input, STDIN_FILENO);
                                                close(input);
                                        }
                                        if(used_output){
                                                //output = redir(STDOUT_FILENO, output)
                                                dup2(output, STDOUT_FILENO);
                                                close(output);
                                        }

                                }
                                close(fd[READ_END]);		//https://stackoverflow.com/questions/40565197/pipe-usage-in-c

                                //if it is not one of the commands:

                                if(execvp(seperated[0], seperated)){
                                    //AshellPrint("\n");
                                    AshellPrint("Failed to execute ");
                                    AshellPrint(seperated[0]);
                                    AshellPrint("\n");
                                    minipwd();
                                    exit(EXIT_FAILURE);

                                }

                                //parent
                                //wait for it to finish
                        }
                        else{
                                        //parent process: child executed, parent wait for child to finish
                                        waitpid(pid, &status, WEXITED); //https://linux.die.net/man/2/waitpid PID
                                        //close fd[WRITE_END];
                                        fd_old = fd[READ_END];





                        }


                }
                AshellPrint("\n");
                //minipwd();
                //OUTSIDE OF FOR





}
void CallPrograms(char **seperated, int * metadata, char * tokens){
    char * run_program = seperated[0]; //the first argument is the program to run
    //wrong - metadata[0] = num_args+1;
    int num_args = metadata[0] - 1; //this is actually num of splits
    if(run_program[0] == 'c' && run_program[1] == 'd' && run_program[2] == '\0'){
        char * directory = seperated[1]; //TODO: check to see if it exists
        cd(directory);
        minipwd();
    }
    else if(run_program[0] == 'l' && run_program[1] == 's' && run_program[2] == '\0'){

        if(metadata[0]>0){ //fixes seg fault - if there is a splitter
            char * directory = seperated[1];
            //char * directory;
            ls(directory);
            minipwd();
        }
        else{
            char * directory = get_current_dir_name();
            ls(); //IF NO ARGS, PASS IN NOTHING
            minipwd();
        }

    }
    else if(run_program[0] == 'p' && run_program[1] == 'w' && run_program[2] == 'd' && run_program[3] == '\0'){

        AshellPrint("\n");
        pwd();
        minipwd();
    }
    else if(run_program[0] == 'e' && run_program[1] == 'x' && run_program[2] == 'i' && run_program[3] == 't' && run_program[4] == '\0'){
        AshellPrint("\n");
        exit();
    }
    else if(run_program[0] == 'f' && run_program[1] == 'f' && run_program[2] == '\0'){
        char * filename = seperated[1];

        const char *file = "ff";
        const char *dir = "fftest";

        dir = get_current_dir_name();
        chdir(get_current_dir_name());
        std::vector<std::string> vec;

        //vec = ffemptdir(file, NULL); //to make Directory and new Dir fftest
        //vec = ffemptdir(file, dir);
        const char *newdir = NULL; //likely seperate[1]
        vec = ff(filename, dir,  newdir);

        AshellPrint("\n");
        for(int i=0; i<vec.size(); ++i){
          //found locations in:
          AshellPrint(vec[i]);
          AshellPrint("\n");
        }
        //ff(filename, dir,  newdir);
        minipwd();
    }
    else{
        exec(seperated, metadata,tokens);
    }



}

void parse(char *prog, char **parsed){

    int metadata[] = {0,0,0,0,0,0};
    //0 - num splits, 1 - num args, 2 - num pipes, 3 - num right, 4 - num left, 5 - num spaces

    char delimit[]=" \<\>\|"; //https://stackoverflow.com/questions/26597977/split-string-with-multiple-delimiters-using-strtok-in-c
    //Parsing char array received, basically a split line function.

    int i = 0;
    int j = 0; //num pipes

    int num_pipes;
    int num_right;
    int num_left;
    int num_spaces;
    int num_tokens;
    char split_memory[110];
    char * split = split_memory;
    char * seperated[15] = {0}; //initialize to zero or seg fault in ls call


    char tokens[10];
    for(int x = 0; x < strlen(prog)+1;++x){
        if(prog[x-1]== '<'){
            num_left++;
            tokens[num_tokens] = '<';
            num_tokens++;


        }
        else if(prog[x-1]== '>'){
            num_right++;
            tokens[num_tokens] = '>';
            num_tokens++;
            tokens[x] = 'b';
        }
        else if(prog[x-1]== '|'){
            num_pipes++;
            tokens[num_tokens] = '|';
            num_tokens++;
        }
        else if(prog[x-1] == ' '){ //may need to be space ascii
            num_spaces++;
            tokens[num_tokens] = ' ';
            num_tokens++;
        }

    }
    metadata[2] = num_pipes;
    metadata[3] = num_right;
    metadata[4] = num_left;
    metadata[5] = num_spaces;

    //http://www.cplusplus.com/reference/cstring/strtok/
    split = strtok(prog, delimit);

    while (split != NULL){
        seperated[i] = split;
        parsed[i] = split;
        split = strtok(NULL, delimit);
        ++i;
        //number of args is i

    }
    seperated[i] = split;

    char * run_program = seperated[0];
    metadata[0] = i -1;

    //Call the correct program now that the data is collected
    CallPrograms(seperated, metadata, tokens);
}

void ReadAndParseCmd() {

    std::string audible_bell = charString('\a'); //audible bell

    bool end_line = false;
    int max_size = 512;  	//TODO: switch to buffer or malloc system if necessary
    int num_chars = 0;		//the num of chars in a line
    int num_lines;
    int num_lines_tot;

    size_t bytes_read = 0;


    //Setting up memory
    char prog_mem[100] = ""; //TODO: find max size
    char args_mem[100] = ""; //TODO: is this read-only memory

    char * prog = prog_mem; //Array containing chars until enter hit
    char *args = args_mem; 	//Input after the command/program

    char hist[10][10];
    char char_read = '\0';


    bool arrow_flag;

    int max_bytes = 1; //reads at most 1 byte at a time


    struct termios SavedTermAttributes; //from noncanmode.c
    SetNonCanonicalMode(0, &SavedTermAttributes); //from noncanmode.c

    while (!end_line){

        int key_location = num_chars-1; //key location is the # of keys pressed in one line
        hist[num_lines_tot][key_location] = prog[key_location]; //sets history on each key press

        bytes_read = read(STDIN_FILENO, &char_read, max_bytes); //STDIN_FILENO may just be 1 TODO


        //EOT (end of transit) CASE *---
        if(0x04 == char_read){ // C-d
            break;
        }

        //ARROW CASE *---
        else if (arrow_flag && 0x5B != char_read){
            if(0x41 == char_read && num_lines != 0){
                //UPARROW
                //Delete old command
                for(int n = 0; n < num_chars + 12; n++){
                    AshellPrint("\b \b");
                }

                num_lines--;			//set line number
                prog = hist[num_lines];         //set program to history
                minipwd();
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
                for(int n = 0; n < num_chars + 12; n++){
                    AshellPrint("\b \b");
                }
                num_lines++;			//set line number
                prog = hist[num_lines];	//set program to history

                minipwd();
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
           //corrects number of chars entered
            prog[num_chars] = char_read;	//replaces location in memory to backspace (maybe should be '\0'?)
        }
        else if (0x7F == char_read && num_chars <= 0){
             AshellPrint(audible_bell);
             num_chars--;
        }

        //STANDARD CASE (if the char can be printed) *---
        else if (isprint(char_read)){
            prog[num_chars] = char_read;					//sets location in memory to the printable char
            std::string str1 = charString(prog[num_chars]);                     //converts prog[i] to string so it can work with AshellPrint
            AshellPrint(str1);                                                  //prints char to shell
        }
        //ENTER CASE *---
        else if (0x0A == char_read) {
           //exit the loop
            end_line = true;
        }
        //ARROW CASE INITIATOR	*---
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
