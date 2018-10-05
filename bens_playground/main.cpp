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

    //Parsing char array received, basically a split line function, in progress

    std::cout << "Call parse: " << "\n";
    std::cout << "PRE SPLIT: prog: " << prog << " parsed: " << *parsed<< "\n";
    int i = 0;
    char split_memory[110];
    char *split = split_memory;

    //http://www.cplusplus.com/reference/cstring/strtok/
    split = strtok(prog, " ");

    while (split != NULL){
        std::cout << "i: " << i << " split: " << split<<"\n";
        parsed[i] = split;
        split = strtok(NULL, " ");
        ++i;
    }


    std::cout << "POST SPLIT: prog: " << prog << " parsed: " << *parsed << " split: " << *split<< "\n";
    std::cout << "parsed[0]: " << parsed[0];


}




int main(int argc, char *argv[]) {

    bool end_line = false;
    int max_size = 512;  //TODO: switch to buffer or malloc system if necessary
    int i = 0;

    char test_array[100] = "12345678";

    //std::cout <<"size of '" << test_array << "' : " <<  size_of(test_array) << "\n";

    size_t bytes_read = 0;

    //if you do this it creates in_one in read-only memory, can't change
    //char *in_one = "one-";





    //std::cout <<"test prog after: " << test_prog << "\n";
    //std::cout <<"test args after: " << test_parsed << "\n";
    //std::cout <<"parsed: " << parsed_char << "\n";

    char char_read = NULL;
    char * prog; //the program contains all input
    char * parsed; //the program contains all input

    //char args[max_size];
    char *args = "hello";

    //char * args;

    //char ** args = NULL; //the arguments are the pieces of the program, seperated by space

    int max_bytes = 1; //reads at most 1 byte at a time
    int fd_read = 0; //this if the fd (file descriptior) for read

    while (!end_line){
        //bytes_read is the number of bytes SUCCESSFULLY read
        //Example: if "Ben" is typed with max_bytes being 10, 4 is returned.
        bytes_read = read(fd_read, &char_read, max_bytes);


        //if the input is
        if (isprint(char_read)){
            //std::cout <<"this comes out: " << prog_print << "\n";
            prog[i] = char_read;
        }

        else if ("0\\") {
            end_line = true;
            //always a null character at the end of the string
            prog[i] = '\0';

            //
            //std::cout << "now at the end of the string \n";
        }


        //std::cout <<"i: " << i << "\n";

        i++;

    }
    std::cout <<"prog:  " << prog << "    args:   " << args<< "\n";
    parse(prog,&args);




}
