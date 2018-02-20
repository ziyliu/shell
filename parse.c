/*
 * Filename: parse.c
 * Author: Zi Ying Liu
 */

#include "parse.h"

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

    comm->varNum = 0;
    comm->command = malloc(sizeof(char)*MAXLINE);
    comm->varList[0] = malloc(sizeof(char)*MAXLINE); 
    

    int i = 0;
    int var_pos = 0;
    /* parse command first */
    while(command[i]!='\n' && command[i]!='\0') {
        if(command[i] == ' ') break;
        comm->command[i] = command[i];
        comm->varList[0][var_pos] = command[i];
        i++;
        var_pos++;
    }

    comm->varList[0][var_pos] = '\0';
    comm->varNum++;

    comm->command[i] = '\0';
    i++;

    var_pos = 0;
    comm->varList[comm->varNum] = malloc(sizeof(char)*MAXLINE);
    /* parse variables if they exist */

    while(command[i]!='\n' && command[i]!='\0') {
        if(command[i]==' ' && (command[i+1]!='\n' && command[i+1]!='\0')) {
            comm->varList[comm->varNum][var_pos] = '\0';
            comm->varNum++;
            comm->varList[comm->varNum] = malloc(sizeof(char)*MAXLINE);
            var_pos = 0;
        }
        else {
            comm->varList[comm->varNum][var_pos] = command[i];
            var_pos++;
        }
        i++;
    }

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

    //support single command first, then move on to pipes
    int i = 0;
    while(cmdLine[i] != '\n' && cmdLine[i] != '\0') {
        command[i] = cmdLine[i];
        
        if(cmdLine[i]=='>') Result->outFileBool = 1;
        if(cmdLine[i]=='<') Result->inFileBool = 1;
        if(cmdLine[i]=='&') Result->bgBool = 1;

        i++;
    }

    command[i] = '\0';

    parse_command(command, &Result->commArray[com_pos]);

    return Result;

}

void print_info(parseInfo* p) {

    printf("print_info: printing info about parseInfo struct\n");

    int i;
    /* print all the arguments */
    for(i=0; i<p->commArray[0].varNum; i++) {
        int argnum = i+1;
        printf("arg%d: %s\n", argnum, p->commArray[0].varList[i]);
    }

    char inpipe[4];
    if(p->inFileBool) strncpy(inpipe, "yes", 4);
    else strncpy(inpipe, "no", 4);

    char outpipe[4];
    if(p->outFileBool) strncpy(outpipe, "yes", 4);
    else strncpy(outpipe, "no", 4);

    char bg[4];
    if(p->bgBool) strncpy(bg, "yes", 4);
    else strncpy(bg, "no", 4);

    printf("inpipe: %s\n", inpipe);
    printf("outpipe: %s\n", outpipe);
    printf("background: %s\n", bg);

    return;
}

void free_info(parseInfo* info) {
    printf("free_info: freeing memory associated to parseInfo struct\n");

    int i;
    for(i=0; i<info->pipeNum; i++) {
        free(info->commArray[i].command);
        int j;
        for(j=0; j<info->commArray[i].varNum; j++) {
            free(info->commArray[i].varList[j]);
        }
    }
    //free each commArray struct inside info
    free(info);

    return;
}
