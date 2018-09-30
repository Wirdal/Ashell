// I/O services

void AshellPrint(char* output){
//TODO
};

size_t AshellRead(int fd, void *buf, size_t count){
//TODO
};

int AshellOpen(const char *path, int flags, .../*, mode_t mode*/){
//TODO
};
// Shell commands


char* pwd(){
//TODO
};

void exit(){
//TODO
};

void cd(char* directory){
//TODO
}; //Will need to deal with the HOME with a default var

char* ls(char* directory){
//TODO
};

char* ff(char* filename){
//TODO
};
