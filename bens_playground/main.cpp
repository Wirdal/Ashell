#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int size_of(char *array){
    int i = 0;

    while(array[i] != '\0'){
        i++;
    }

    return i;

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
        std::cout <<"seperated[" << i << "] "<< seperated[i] << "\n";
        parsed[i] = split;
        //Not sure what split becomes
        split = strtok(NULL, " ");
        ++i;
    }

    std::cout << "\n\n";

    char * run_program = seperated[0];
    int num_args = i -1;

    std::cout <<"Run Program: " << run_program<<"\n";
    std::cout <<"Number of Args: " << num_args<<"\n";



    //SWITCH run_program == "cd"
    //SWITCH run_program == "ls"
    //SWITCH run_program == "pwd"


}




int main(int argc, char *argv[]) {

    bool end_line = false;
    int max_size = 512;  //TODO: switch to buffer or malloc system if necessary
    int i = 0;

    char test_array[100] = "12345678";

    size_t bytes_read = 0;

    //if you do this it creates in_one in read-only memory, can't change
    //char *in_one = "one-";


    char char_read = NULL;
    char * prog; //the program contains all input
    char * parsed; //to contain parsed input
    char *args = ""; //Input after the command/program

    int max_bytes = 1; //reads at most 1 byte at a time
    int fd_read = 0; //this if the fd (file descriptor) for read

    while (!end_line){
        //bytes_read is the number of bytes SUCCESSFULLY read
        //Example: if "Ben" is typed with max_bytes being 10, 4 is returned.
        bytes_read = read(fd_read, &char_read, max_bytes);


        //if the input is readable
        if (isprint(char_read)){
            //std::cout <<"this comes out: " << prog_print << "\n";
            prog[i] = char_read;
        }

        else if ("0\\") {
            end_line = true;
            //always a null character at the end of the string
            prog[i] = '\0';

        }



        i++;

    }
    std::cout <<"prog:  " << prog << "    args:   " << args<< "\n\n";
    parse(prog,&args);
    std::cout <<"Done."<< "\n";





}
