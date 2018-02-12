
#include "parse.h"

#define MAXLINE 81

int main(int agrc, char** argv) {

    char* cmdLine;
    cmdLine = malloc(sizeof(char)*MAXLINE);

    parseInfo* info;
    
    while(1) { //change condition
        //cmdLine = readline(printPrompt());

        info = parse(cmdLine);
        
        //print if there is input direction
        print_info(info);
    }

    free_info(info);
}

/* prompt the user to input a command */
void printPrompt() {
}

//char* readline
