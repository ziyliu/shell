/*
 * Filename: parse.c
 * Author: Zi Ying Liu
 */

#include "parse.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 81

void init_info(parseInfo* p) {
    printf("init_info: initializing parseInfo\n");

    //allocate commArray on the heap
    p->commArray = (struct commandType*) 
                   malloc(PIPE_MAXLINE, sizeof(commandType));
      
}

void parse_command(char* command, struct commandType* comm) {
    printf("parse_command: parsing a single command\n");
    //populate commandType struct with command string

    commandType->command = command;
    commandType->varNum++;
    
}

parseInfo* parse(char* cmdLine) {

    parseInfo* Result;
    char command[MAXLINE];
    int com_pos = -1;

    if(cmdLine[-1]=='\n' && cmdLine[-1]=='\0') return NULL;
    Result = malloc(sizeof(parseInfo));
    init_info(Result);
    cmd_pos = 0;

    while(i=cmd_pos; i<MAXLINE; i++) {
        if(cmdLine[i]==' ') break;
        else {
            command[i]=cmdLine[i];
        }
    }

    command[com_pos]='\0';
    parse_command(command, Result->commArray);

    return Result;
}

void print_info(parseInfo* p) {

    printf("print_info: printing info about parseInfo struct\n");
    //printf("%: filename of program to execute &\n");

    int i;
    /* print all the arguments */
    for(i=0; p->pipeNum; i++) {
        int argnum = i+1;
        printf("arg%d: %s\n", argnum, p->commArray[i]);
    }
    
    char* inpipe;
    if(p->inFileBool) inpipe = "yes";
    else inpipe = "no";

    char* outpipe;
    if(p->outFileBool) outpipe = "yes";
    else outpipe = "no";

    char* bg;
    if(p->bgBool) bg = "yes";
    else bg = "no";

    printf("inpipe: %s\n", inpipe);
    printf("outpipe: %s\n", outpipe);
    printf("background: %s\n", bg);

}

void free_info(parseInfo* info) {
    free(info);
}
