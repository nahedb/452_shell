#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

int display_prompt(){
    char hostname[1024];
    gethostname(hostname, 1023);
    printf("[%s]: ",hostname);

}

int read_commands(char* cmd, char* parm){
    char command[35];
    fgets(command, 35, fp);
    cmd = strtok(command, " ");
    parm = strtok(NULL, " ");

}

int main(int argc, char* argv[]) 
{
    printf("Welcome to my Shell! \nPlease enter a command.");
    pid_t pid;
    char* command, parm;
    int * status;
    while(1){
        display_prompt();
        read_commands(&command, &parm);
        if(command == "quit"){
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
            execvp(command, &command);
            exit(1);
        }

    }
    
}
