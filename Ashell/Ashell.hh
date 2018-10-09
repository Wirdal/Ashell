#ifndef ASHELL_H
#define ASHELL_H
#include <string>
#include <vector>
/*
This file is meant to go over the implementation for Ashell.
Probaby will be more here, but define implemetnation here first
*/


// I/O services
void AshellPrint(const char* output);
void AshellPrint(std::string output);
void AshellPrint(int output);

//Path: Name of the file to open. It includes the file path defining where to open or create a file
//Flag: The permissiosn given to us by the file; performed by bitwise OR
//Returns: A handle that we use to refer to that file
int AshellOpen(const char *path, int flags, .../*, mode_t mode*/);


//FD, is the handle returned by open
//Buf, the buffer where the read data is stored to
//Size_t, number of bytes to be read from the file
size_t AshellRead(int fd, void *buf, size_t count); //Maybe will need more?

// Shell commands


void pwd();

void exit();

void cd(char* directory);

void ls(char* directory);
void ls(std::string directory);
void ls();

std::vector<char*> ff(const char* filename, const char* directory);

// Reading


int size_of(char *array);

void CallPrograms(char **seperated, int num_args);

void parse(char *prog, char **parsed);

void ReadAndParseCmd();


#endif
