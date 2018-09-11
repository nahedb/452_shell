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
    char * enter = strtok(cmd, '\n');
    if(enter != NULL){
        enter = '\0';
    }
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
    char command[300], quit[5] = "quit";
    char* parm[300];
    int * status;
    while(1){
        display_prompt();
        fgets(command, 300, stdin);
        read_commands(command, &parm);
        if(strcmp(&parm[0], quit) == 0){
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
            execvp(parm[0], parm);
            printf("Command not known.");
            exit(1);
        }

    }
    return 0;
}
