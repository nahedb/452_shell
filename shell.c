#include <stdio.h> 
#include <sys/types.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>

int display_prompt(){
    // char hostname[1024];
    // gethostname(hostname, 1023);
    // printf("[%s]: ",hostname);
    printf("[shell]:");
    return 0;
}

int read_commands(char* cmd, char** token){
    char *pos;
    if((pos=strchr(cmd, '\n')) != NULL){
        *pos = '\0';
    }   
    int count = 0;
    char * tempcmd;
    tempcmd = strtok(NULL, " ");
    while(tempcmd != NULL){
        token[count] = tempcmd;
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
    // char* token = NULL;
    int status;
    while(1){
        display_prompt();
        fgets(command, 300, stdin);
        while(command[0] == '\n' || command[0] == ' '){
            display_prompt();
            fgets(command, 256, stdin);
        }   


        char* args[];
        char* token = strtok(command, " ");

        int counter = 0;
        while (token != NULL) { 
            printf("%s ", token); 
            argv[counter] = token;
            counter++;
            token = strtok(NULL, " "); 
        } 
        
        argv[counter] = NULL;
        
        for (int i = 0; i < argv; ++i)
        {
            printf("argv[%d]: %s\n", i, argv[i]);
        }

                
        printf("Hit\n");

      
        pid = fork();
        if(pid < 0){
            perror("fork failure"); 
            exit(1); 
        }
        else if (pid){
            waitpid(pid, &status, 0);
        }
        else{
            // printf("%s\n", token);
            execvp(argv[0], argv);
            printf("Command not known.\n");
            exit(1);
        }

    }
    return 0;
}
