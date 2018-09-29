#ifndef ASHELL_H
#define ASHELL_H

/*
This file is meant to go over the implementation for Ashell.
Probaby will be more here, but define implemetnation here first
*/


// I/O services


void AshellPrint(char* output);

char* AshellRead(const char* path); //Maybe will need more?

// Shell commands


char* pwd(); // May need a path arguement

void exit();

void cd(char* directory); //Will need to deal with the HOME with a default var

char* ls(char* directory);

char* ff(char* filename);

#endif
