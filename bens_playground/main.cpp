#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {

    bool end_line = false;
    int max_size = 512;  //TODO: switch to buffer or malloc system if necessary
    int i = 0;


    size_t bytes_read = 0;

    char prog_print = NULL;\
    char prog[max_size];
    char ** args = NULL; //points to a set of pointers of char arrays
    char command[10];

    int max_bytes = 1; //reads at most 1 byte at a time
    int fd_read = 0; //this if the fd (file descriptior) for read

    while (!end_line){
        //bytes_read is the number of bytes SUCCESSFULLY read
        //
        bytes_read = read(fd_read, &prog_print, max_bytes);

        if (isprint(prog_print)){
            std::cout <<"this comes out: " << prog_print << "\n";
            prog[i] = prog_print;
        }

        else if ("0\\") {
            end_line = true;
            prog[i] = '\0';
            //std::cout << "now at the end of the string \n";
        }


        //std::cout <<"i: " << i << "\n";

        i++;

    }
    std::cout <<"prog:  " << prog << "\n";



}