#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int size_of(char *array){
    int i = 0;

    while(array[i] != '\0'){
        i++;
    }

    return i;

}


void parse(char *prog, char *parsed){

    //Parsing char array received, basically a split line function, in progress

    std::cout << "Call parse: " << "\n";
    char splitter = ' ';

    char *input;
    int i = 0;
    int space_loc = 0;
    int num_spaces = 0;
    char command[5];
    char argument[514];
    //char** arg_list = new char*[100]; //100 should be the num of possible arrays


    input = prog;

    std::cout << "prog: " << prog << " input: " << input << " parsed: " << parsed<< "\n";

    while(input[i] != '\0'){
        //If a space is found
        if(input[i] == splitter){
            num_spaces++;
            space_loc=i;

            //if this is the first space found
            if(num_spaces == 1){
                for(int a = 0; a < i; ++a){
                    command[a] = input[a];
                    //std::cout << "put in command: "<< input[a] << "\n";
                }
                command[i] = '\0';
            }

        }
        if(input[i+1] == '\0'){
            for(int a = 0; a < i - space_loc; ++a){
                argument[a] = input[a + space_loc + 1];
                argument[a + 1] = '\0';

            }
            argument[i+1] = '\0';

        }

        //std::cout << "input at i:  "<< input[i] << "\n";
        i ++;


    }

    std::cout << "Command: "<< command << "\n";
    std::cout << "Arg: "<< argument << "\n";

    //Return parsed arrays
    std::cout << "returned array: " << parsed<< "\n";


}




int main(int argc, char *argv[]) {

    bool end_line = false;
    int max_size = 512;  //TODO: switch to buffer or malloc system if necessary
    int i = 0;

    char test_array[] = "12345678";

    std::cout <<"size of '" << test_array << "' : " <<  size_of(test_array) << "\n";

    size_t bytes_read = 0;

    //if you do this it creates in_one in read-only memory, can't change
    //char *in_one = "one-";
    char test_prog[] = "cd home";
    char test_parsed[] = "arg1 arg2 arg3";


    parse(test_prog, test_parsed);

    std::cout <<"test prog after: " << test_prog << "\n";
    std::cout <<"test args after: " << test_parsed << "\n";
    //std::cout <<"parsed: " << parsed_char << "\n";

    char char_read = NULL;
    char prog[max_size]; //the program contains all input
    char * parsed; //the program contains all input
    char ** args = NULL; //the arguments are the pieces of the program, seperated by space

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
            //std::cout << "now at the end of the string \n";
        }


        //std::cout <<"i: " << i << "\n";

        i++;

    }
    std::cout <<"prog:  " << prog << "\n";



}
