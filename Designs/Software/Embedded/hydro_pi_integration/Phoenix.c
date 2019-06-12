#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define FALSE 0
#define TRUE 1
#define ERROR -1
#define PIPE_IN  pipeFd[0]
#define PIPE_OUT pipeFd[1]
#define STDIN 0
#define STDOUT 1
#define STDERROR 2
#define CWD_BUFF_SIZE 1024
#define DIR "/home/pi/Hydro/Designs/Software/Embedded/hydro_pi_integration/hydro_pi"

//#define DISPLAY_EXE_ARGS

typedef enum Errors_t{
    ERROR_CMD,
    ERROR_FORK,
    ERROR_PIPE,
}Errors_t;

int main()
{
    pid_t       executePid;
    int         pipeFd[2];
    int         status;
    char *      outFile = NULL;
    char *      homeDir = NULL;
    
    static char * exeArgs[] =  {DIR, NULL};
    
    while(1){
        if((executePid = fork()) < 0){
            perror("Execute Fork");
        }
        //Child
        if(executePid == 0){
            status = execvp(exeArgs[0], exeArgs);
            if(status == -1){
                exit(ERROR_CMD);
            }
        }
        //Parent
        else{
            waitpid(executePid,NULL,WEXITED);
        }
    }
}
    
    
    
