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

    p->inFileBool = 0;
    p->outFileBool = 0;
    p->bgBool = 0;

    p->pipeNum = 0;

}

void parse_command(char* command, struct commandType* comm) {
    printf("parse_command: parsing a single command\n");

    comm->command = command;
    comm->varNum++;
    
}

parseInfo* parse(char* cmdLine) {

    parseInfo* Result;
    char command[MAXLINE];
    int com_pos = -1;

    /* empty command */
    if(cmdLine[com_pos]=='\n' && cmdLine[com_pos]=='\0') return NULL;

    /* Allocate Result struct on the heap and initialize */
    Result = malloc(sizeof(parseInfo));
    init_info(Result);

    com_pos = 0;

    int i;
    for(i=com_pos; i<MAXLINE; i++) {
        if(cmdLine[i]==' ') break;
        else {
            command[i]=cmdLine[i];
        }
    }

    /* null-truncate the string */
    com_pos = i;
    command[com_pos]='\0';

    parse_command(command, Result->commArray);

    return Result;
}

void print_info(parseInfo* p) {

    printf("print_info: printing info about parseInfo struct\n");
    //printf("%: filename of program to execute &\n");

    int i;
    /* print all the arguments */
    for(i=0; i<p->pipeNum; i++) {
        int argnum = i+1;
        printf("arg%d: %s\n", argnum, p->commArray[i].command);
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
    printf("free_info: freeing memory associated to parseInfo struct\n");
    free(info);
}
