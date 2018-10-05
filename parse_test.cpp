#include <fcntl.h>
#include <iostream>
#include <unistd.h>



void parse(char *prog, char *parsed){

    //Parsing char array received, basically a split line function, in progress

    std::cout << "Call parse: " << "\n";
    char splitter = ' ';
    char in[100];
    char *input = in;
    int num_spaces[2];
    int i = 0;
    int split_loc = 0;
//  int num_spaces = 0;
    char command_mem[5];
    char *command = command_mem;
    char argument[10];


    char arg_list[12];

    /*
    char** arg_list = new char*[max_num_split]; //max_num_split should be the num of possible arrays
    for(int j = 0; j < max_num_split ; ++j){
        arg_list[j] = new char[10];
    }
    */

    input = prog;

    std::cout << "prog: " << prog << " input: " << input << " parsed: " << parsed<< "\n";

    while(input[i] != '\0'){
        //If a space is found
        //std::cout << "i: " << i  << "\n";
        if(input[i] == splitter){
            //num_spaces=num_spaces + 1; BUG: this results in num_spaces = 25965 on third iteration
            //maybe running out of memory

            split_loc=i;
            num_spaces[1] = num_spaces[1] + 1;
            //std::cout << "Arg List at num_spaces = " << num_spaces[0] << ": " << "\n";

            for(int a = 0; a < i; ++a){
                std::cout << "a: " << a << " < i: " << i << "\n";
                command[a] = input[a];
                //std::cout << "put in command: "<< input[a] << "\n";
            }

            std::cout << "if"<< "\n";
            //for 2D array
            //arg_list[num_spaces] = command;
            std::cout << "numspaces: " << num_spaces[1] << "\n";
            arg_list[num_spaces[0]] = command[0];

            std::cout << "Arg List at num_spaces = " << num_spaces[1] << ": " << arg_list[num_spaces[1]] << "\n";



            command[i] = '\0';
        }


        if(input[i+1] == '\0'){
            for(int a = 0; a < i - split_loc; ++a){
                argument[a] = input[a + split_loc + 1];
                argument[a + 1] = '\0';

            }

            argument[i+1] = '\0';

        }

        i++;


    }

    std::cout << "Command: "<< command << "\n";
    std::cout << "Arg: "<< argument << "\n";

    //Return parsed arrays
    std::cout << "returned array: " << parsed << "\n";


}




int main(int argc, char *argv[]) {

    char test_prog[] = "cd home now r";
    char test_parsed[] = "arg1 arg2 arg3 arg4";
    char *a = test_prog;
    char *b = test_parsed;


    parse(a, b);



}
