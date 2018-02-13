/*
 * Zi Ying Liu
 */

#include "parse.h"

#define MAXLINE 81

enum BUILTIN_COMMANDS { NO_SUCH_BUILTIN=0, EXIT, JOBS };

char* buildPrompt() {
    return "%";
}

/*char* readline(char* prompt) {
    char* cmdLine;
    printf("%s", prompt);

    return cmdLine;
}*/

int isBuiltInCommand(char* cmd) {
    if(strncmp(cmd, "exit", strlen("exit"))==0) return EXIT;

    return NO_SUCH_BUILTIN;

}

int main(int agrc, char** argv) {

    char* cmdLine;
    parseInfo* info;
   
    #ifdef UNIX
        fprintf(stdout, "This is the UNIX version\n");
    #endif

    #ifdef WINDOWS
        fprintf(stdout, "This is the WINDOWS version\n");
    #endif

    while(1) { //change condition

        cmdLine = malloc(sizeof(char)*MAXLINE);
        #ifdef UNIX
            cmdLine = readline(buildPrompt());
            if(cmdLine==NULL) {
                fprintf(stderr, "Unable to read command\n");
                continue;
            }
        #endif

        info = parse(cmdLine);
        if(info == NULL) {
            free(cmdLine);
            continue;
        }

        //print if there is input direction
        print_info(info);
        free_info(info);
        free(cmdLine);
    }

    
    return 0;
}

