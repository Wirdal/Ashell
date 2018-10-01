#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
int main (int argc, char *argv[]) {
	 int fd;
	 const char path[10] = "tests.cpp";
	 fd = open(path ,O_WRONLY); 
	 std::cout << fd << "Hello!";
}