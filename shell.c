#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

int display_prompt(){
    char hostname[1024];
    gethostname(hostname, 1023);
    printf("[%s]: ",hostname);
    return 0;
}

int read_commands(char* cmd, char** parm){
    cmd = strtok(cmd, " ");
    int count = 0;
    char * tempcmd;
    tempcmd = strtok(NULL, " ");
    while(parm != NULL){
        parm[count] = tempcmd;
        tempcmd = strtok(NULL, " ");
        count++;
    }
    return 0;
}

int main(int argc, char* argv[]) 
{
    printf("Welcome to my Shell! \nPlease enter a command.\n");
    pid_t pid;
    char command[300];
    char* parm, quit;
    int * status;
    quit = "quit";
    while(1){
        display_prompt();
        fgets(command, 300, stdin);
        read_commands(&command, &parm);
        if(strcmp(command, quit) == 0){
            printf("Quit");
            break;
        }
        pid = fork();
        if(pid < 0){
            perror("fork failure"); 
            exit(1); 
        }
        else if (pid){
            waitpid(pid, &status, 0);
        }
        else{
            execlp(command, &parm, 0);
            printf("Command not known.");
            exit(1);
        }

    }
    return 0;
}
