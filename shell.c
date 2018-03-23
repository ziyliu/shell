/*
 * Zi Ying Liu
 */

#include <errno.h>
#include "parse.h"

#define MAXLINE 81
#define ROOT "."

enum BUILTIN_COMMANDS { NO_SUCH_BUILTIN=0, EXIT, JOBS };

char* buildPrompt(char* path_buf) {
    int path_size = pathconf(ROOT, _PC_PATH_MAX);
    char* path;

    if((path_buf = (char*)malloc((size_t)path_size))!=NULL) {
        path = getcwd(path_buf, (size_t)path_size);       
    }

    if(path!=NULL) {
        strncat(path, "% ", strlen(path)+3);
    }

    return path;
}

int isBuiltInCommand(char* cmd) {
    if(strncmp(cmd, "exit", strlen("exit"))==0) return EXIT;

    return NO_SUCH_BUILTIN;

}

int main(int agrc, char** argv) {

    char* cmdLine;
    parseInfo* info;
    struct commandType* com;
   
    #ifdef UNIX
        fprintf(stdout, "This is the UNIX version\n");
    #endif

    #ifdef WINDOWS
        fprintf(stdout, "This is the WINDOWS version\n");
    #endif

    while(1) { //change condition

        int childPID;

        cmdLine = malloc(sizeof(char)*MAXLINE);
        #ifdef UNIX
        char* path_buf;
        cmdLine = readline(buildPrompt(path_buf));
        if(cmdLine==NULL) {
            fprintf(stderr, "Unable to read command\n");
            continue;
        }
        #endif

        //TODO:
        //make sure absolute/relative paths are supported
        //history and other flags here

        info = parse(cmdLine);
        if(info == NULL) {
            free(cmdLine);
            continue;
        }


        //print if there is input direction
        print_info(info);

        com = &info->commArray[0];
        if((com == NULL) || (com->command==NULL)) {
            free_info(info);
            free(cmdLine);
            continue;
        }
  

        //com->command tells the command name of com

        if(isBuiltInCommand(com->command) == EXIT) exit(1);
         
        free_info(info);
        free(cmdLine);
        free(path_buf);
    }

    exit(0);
}

