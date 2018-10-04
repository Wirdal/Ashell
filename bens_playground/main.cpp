#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int max_size = 10;
    int i = 0;
    char prog = NULL;
    char prog_print = NULL;
    char arg = NULL;



    while (i < max_size){

        size_t bytes_read = read(0, &prog, 10);
        //read(0, &prog_print, 1);
        std::cout <<"bytes_read: " << bytes_read << "\n";
        if (isprint(prog)){
            //std::cout <<"this comes out: " << prog_print << "\n";

        }
        else if ("0\\") {
            std::cout << "now at the end of the string \n";

        }


    }
    //const char *input = "hello world";
    //std::string input;


}
