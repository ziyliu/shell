/*
 * Zi Ying Liu
 */

#include "parse.h"

#define MAXLINE 81


char* readline() {
    char* cmdLine;
    scanf("%s", cmdLine);

    return cmdLine;
}

void printPrompt() {
    printf("/usr/foo%%");
}

int main(int agrc, char** argv) {

    char* cmdLine;
    cmdLine = malloc(sizeof(char)*MAXLINE);

    parseInfo* info;
    
    while(1) { //change condition
        printPrompt();
        cmdLine = readline();

        info = parse(cmdLine);
        
        //print if there is input direction
        print_info(info);
    }

    free_info(info);

    return 0;
}

