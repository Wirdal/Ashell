#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


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
    char *path = "home";
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

void CallPrograms(char **seperated, int num_args){
    char * run_program = seperated[0];

    if(run_program[0] == 'c' && run_program[1] == 'd' && run_program[2] == '\0'){
        std::cout <<"Execute CD "<<"\n";

        char * directory = seperated[1]; //TODO: check to see if it exists
        std::cout <<"directory "<< directory <<"\n";
        //cd(directory);
    }
    else if(run_program[0] == 'l' && run_program[1] == 's' && run_program[2] == '\0'){
        std::cout <<"Execute LS "<<"\n";
        //TODO: ls(directory);
    }
    else if(run_program[0] == 'p' && run_program[1] == 'w' && run_program[2] == 'd' && run_program[3] == '\0'){
        std::cout <<"Execute PWD "<<"\n";
        //pwd();
    }
    else if(run_program[0] == 'e' && run_program[1] == 'x' && run_program[2] == 'i' && run_program[3] == 't' && run_program[4] == '\0'){
        std::cout <<"Execute EXIT "<<"\n";
        exit();
    }
    else if(run_program[0] == 'f' && run_program[1] == 'f' && run_program[2] == '\0'){
        std::cout <<"Execute ff "<<"\n";
        char * filename = seperated[1];
        std::cout <<"Filename:  "<< filename <<"\n";
        //TODO: ff(filename);
    }
    else{
        std::cout <<"Run Exec(" << run_program<<");" <<"\n";
        //TODO: exec(program_name)
    }


}

void parse(char *prog, char **parsed){
    //Parsing char array received, basically a split line function.
    //Currently seperates with ' ' TODO work with any character


    int i = 0;
    char split_memory[110];
    char * split = split_memory;
    char * seperated[15];

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
    int max_size = 512;  //TODO: switch to buffer or malloc system if necessary
    int i = 0;

    char test_array[100] = "12345678";

    size_t bytes_read = 0;

    //if you do this it creates in_one in read-only memory, can't change
    //char *in_one = "one-";

    char prog_mem[100] = ""; //should be large?
    char args_mem[100] = ""; //should b 16 (max can show on terminal)?

    char char_read = '\0';
    char * prog = prog_mem; //the program contains all input
    char * parsed; //to contain parsed input
    char *args = args_mem; //Input after the command/program
    bool arrow_flag;

    int max_bytes = 1; //reads at most 1 byte at a time

    //this may need to be STDIN_FILENO
    int fd_read = 0; //this if the fd (file descriptor) for read


    struct termios SavedTermAttributes; //from noncanmode.c
    SetNonCanonicalMode(0, &SavedTermAttributes); //from noncanmode.c

    while (!end_line){
        //bytes_read is the number of bytes SUCCESSFULLY read
        //Example: if "Ben" is typed with max_bytes being 10, 4 is returned.
        //std::cout <<"got to while" << "\n";
        bytes_read = read(STDIN_FILENO, &char_read, max_bytes);


        //if the input is readable
        if(0x04 == char_read){ // C-d
            std::cout <<"its something else entirely..." << "\n";
            break;
        }
        //BACKSPACE CASE
        else if (0x7F == char_read){
            //std::cout <<"got to if" << "\n";
            //std::cout <<"got to if" << "\n";
            AshellPrint("\b \b");
            prog[i] = char_read;
            //std::cout <<"this comes out: " << prog << "\n";

        }
        //ARROW CASE
        else if (arrow_flag && 0x5B != char_read){

            //std::cout <<"ARROW2" << "\n";


            if(0x41 == char_read){
                //UPARROW
                AshellPrint("UPARROW");
                arrow_flag = false;
            }
            else if(0x42 == char_read){
                //DOWNARROW
                AshellPrint("DOWNARROW");
                arrow_flag = false;
            }
            else if(0x43 == char_read){
                //RIGHTARROW
                AshellPrint("RIGHTARROW");
                arrow_flag = false;
            }
            else if(0x44 == char_read){
                //LEFTARROW
                AshellPrint("LEFTARROW");
                arrow_flag = false;
            }
            else{
                //ERROR, shouldn't happen
            }


        }
        else if (arrow_flag && 0x5B == char_read){

            arrow_flag = true;

        }

        else if (isprint(char_read)){
            //these lines don't fix it
            prog[i] = char_read;
            //char dec_to_char = prog[i];
            //std::cout << "prog[i]: " << prog[i] <<"\n"; //getting the decimal representation
            std::string str1 = charString(prog[i]);
            AshellPrint(str1);

        }
        //ENTER CHASE
        else if (0x0A == char_read) {
            std::cout <<"got to end line - so we think 1" << "\n";
            end_line = true;
            //always a null character at the end of the string
            //prog[i] = '\0';

        }
        else{
            //std::cout <<"char(" << char_read<<")";
            //ARROW CASE
            //AshellPrint("ARROW");
            arrow_flag = true;
            //end_line = true;
            //always a null character at the end of the string
            //prog[i] = '\0';

        }
        //std::cout <<"out of if" << "\n";
        i++;

    }
    ResetCanonicalMode(STDIN_FILENO, &SavedTermAttributes);
    //std::cout <<"prog:  " << prog << "    args:   " << args<< "\n\n";
    parse(prog,&args);
    //std::cout <<"Done."<< "\n";


}
int main(int argc, char *argv[]) {
    while(1){
        ReadAndParseCmd();
    }

}
