#ifndef PARSE_H
#define PARSE_H

/* global variables */
#define MAX_VAR_NUM 10
#define PIPE_MAX_NUM 10
#define FILE_MAX_SIZE 40

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct commandType {
    char* command;
    char* varList[MAX_VAR_NUM];
    int varNum;
};

typedef struct {
    int inFileBool;
    int outFileBool;
    int bgBool;
    struct commandType commArray[PIPE_MAX_NUM];
    int pipeNum;
    char inFile[FILE_MAX_SIZE];
    char outFile[FILE_MAX_SIZE];
} parseInfo;

void init_info(parseInfo *p);

void parse_command(char* command, struct commandType *comm);

parseInfo *parse(char* cmdLine);

void free_info(parseInfo *info);

#endif
