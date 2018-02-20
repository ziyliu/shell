/*
 * Zi Ying Liu
 */

#include "parse.h"

#define MAXLINE 81

enum BUILTIN_COMMANDS { NO_SUCH_BUILTIN=0, EXIT, JOBS };

char* buildPrompt() {
    return "/usr/foo% ";
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

        //int childPID;

        cmdLine = malloc(sizeof(char)*MAXLINE);
        #ifdef UNIX
        
        cmdLine = readline(buildPrompt());
        if(cmdLine==NULL) {
            fprintf(stderr, "Unable to read command\n");
            continue;
        }
        #endif

        //history and other flags here

        info = parse(cmdLine);
        if(info == NULL) {
            free(cmdLine);
            continue;
        }

        //print if there is input direction
        print_info(info);


        /*
        com = &info->CommArray
        if((com == NULL) || (comm->command==NULL)) {
            free_info(info)
            free(cmdLine);
            continue;
        }
        */

        //com->command tells the command name of com

        //if(isBuiltInCommand(com->command) == EXIT) exit(1);
         
        free_info(info);
        free(cmdLine);
    }

    
    exit(0);
}

