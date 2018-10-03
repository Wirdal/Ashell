#ifndef ASHELL_H
#define ASHELL_H

/*
This file is meant to go over the implementation for Ashell.
Probaby will be more here, but define implemetnation here first
*/


// I/O services

//Path: Name of the file to open. It includes the file path defining where to open or create a file
//Flag: The permissiosn given to us by the file; performed by bitwise OR
//Returns: A handle that we use to refer to that file
int AshellOpen(const char *path, int flags, .../*, mode_t mode*/);

//
void AshellPrint(const char* output);

//FD, is the handle returned by open
//Buf, the buffer where the read data is stored to
//Size_t, number of bytes to be read from the file
size_t AshellRead(int fd, void *buf, size_t count); //Maybe will need more?

// Shell commands


char* pwd(); // May need a path arguement

void exit();

void cd(char* directory); //Will need to deal with the HOME with a default var

char* ls(char* directory);

char* ff(char* filename);

#endif
