#include <stdio.h> 
#include <sys/types.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>

int display_prompt(){
    char hostname[1024];
    gethostname(hostname, 1023);
    printf("[%s]: ",hostname);
    return 0;
}

int read_commands(char* cmd, char** token){
    char *pos;
    if((pos=strchr(cmd, '\n')) != NULL){
        *pos = '\0';
    }   
    int count = 0;
    char * tempcmd;
    tempcmd = strtok(cmd, " ");
    while(tempcmd != NULL){
        token[count] = tempcmd;
        tempcmd = strtok(NULL, " ");
        count++;
    }
    token[count] = NULL;
    return 0;
}

int main(int argc, char* argv[]) 
{
    printf("Welcome to my Shell! \nPlease enter a command.\n");
    pid_t pid;
    char command[300];
    char* token[15];
    int status;
    while(1){
        display_prompt();
        fgets(command, 300, stdin);
        while(command[0] =='\n' || command[0] == ' '){
            display_prompt();
            fgets(command, 300, stdin);
        }   
        read_commands(command, token);
        if(strcmp(token[0], "quit") == 0){
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
            execvp(token[0], token);
            printf("Command not known.\n");
            exit(1);
        }

    }
    return 0;
}
