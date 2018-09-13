#include <stdio.h> 
#include <sys/types.h> 
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/resource.h>

/* Brendan Nahed and Hunter Hubers
*  CIS 452 Computer Operating Systems
*  September 10, 2018
*/

int display_prompt(){
    // This is the display prompt to the user that is before every command. 
    char hostname[1024];
    gethostname(hostname, 1023);
    printf("[%s]: ",hostname);
    return 0;
}

int read_commands(char* cmd, char** token){
    
    char *pos;

    // Operation to remove the \n at the end of the char array.
    if((pos=strchr(cmd, '\n')) != NULL){
        *pos = '\0';
    }   
    int count = 0;
    char * tempcmd;
    tempcmd = strtok(cmd, " ");

    /* This operation tokenizes the command and stores each token 
    *  initially into tempcmd and then into the array of token at count.
    */
    while(tempcmd != NULL){
        token[count] = tempcmd;
        tempcmd = strtok(NULL, " ");
        count++;
    }

    /* Adds a NULL statement in the last place in the Char array 
    *  of token. This allows execvp to stop at NULL.
    */
    token[count] = NULL;
    return 0;
}

int main(int argc, char* argv[]) {
    printf("Welcome to my Shell! \nPlease enter a command.\n");
    
    // pid is the Child id. 
    pid_t pid;
    
    // Command in the input recieved from the user.
    char command[300];
    
    struct rusage x; 
    struct timeval start;
    struct timeval end;
    

    // Token is a char array to store the tokenized command from the user.
    char* token[15];
    
    // Status holds the status of the child.
    int status;
    
    while(1){
        display_prompt();
        fgets(command, 300, stdin);
        
        // While loop to check for empty commands.
        while(command[0] =='\n' || command[0] == ' '){
            display_prompt();
            fgets(command, 300, stdin);
        }   
        read_commands(command, token);
        if(strcmp(token[0], "quit") == 0){
            break;
        }
        
        // Fork to create the parent and child. Stores the Child in pid.
        pid = fork();
        
        getrusage(RUSAGE_SELF, &x);
        start=x.ru_utime;

        // Failed fork catch.
        if(pid < 0){
            perror("fork failure"); 
            exit(1); 
        }

        // Shell Blocks.
        else if (pid){
            waitpid(pid, &status, 0);
            getrusage(RUSAGE_SELF, &x);
            end = x.ru_utime;
            // Print Resource Usage Statistics
            printf("User CPU time was: %ld.%ds\n", end.tv_sec-start.tv_sec, end.tv_usec-start.tv_usec);
            printf("There where %ld involuntary context switches.\n", x.ru_nivcsw);
        } else { // Child Runs
            execvp(token[0], token);
            printf("Command not known.\n");
            exit(1);
        }

    }
    return 0;
}
