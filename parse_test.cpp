#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
int main (int argc, char *argv[]) {
    //Parsing char array received, basically a split line function, in progress

    int i = 0;
    
    char input[] = "cd home/go";
    //std::cout << "Command typed: " << input << "\n";
    int space_loc = 0;
	int num_spaces = 0;
    char command[5];
    char argument[514];
    
    while(input[i] != '\0'){
	//If a space is found
        if(input[i] == ' '){
	  	num_spaces++;
	   	space_loc=i;

		//if this is the first space found
	   	if(num_spaces == 1){
		    for(int a = 0; a < i; ++a){
		        command[a] = input[a];
			std::cout << "put in command: "<< input[a] << "\n";
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

	std::cout << "input at i:  "<< input[i] << "\n";
        i ++;
	
        
    }

	std::cout << "Command: "<< command << "\n";
	std::cout << "Arg: "<< argument << "\n";
    
    
}
