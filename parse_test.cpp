#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
int main (int argc, char *argv[]) {
    //Parsing char array received, basically a split line function, in progress

    int i = 0;
    
    char input[] = "cd example";
    std::cout << "Command typed: " << input << "\n";
    
    char command[2];
    char argument[10];
    
    while(input[i] != '\0'){
        if(input[i] == ' '){
            for(int a = 0; a < i; ++a){
                command[a] = input[a];
            }
            std::cout << "command: "<< command << "\n";
        }
        
        std::cout << input[i]<<" " << i << "\n";
        i ++;
        
    }
    
    
}
