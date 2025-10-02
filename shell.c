/* Author: Karla Mejia
Shell Project

This code is provided here solely for educational and portfolio purposes.  
No permission is granted to copy, modify, or redistribute this code.  

*/

#include <stdio.h>      // needed for various C basic functions
#include <string.h>     // needed for various string functions
#include <stdlib.h>     // needed for exit()
#include <unistd.h>     // needed for many Linux/Unix functions (eg. fork)
#include <sys/types.h>  // needed for waitpid()
#include <sys/wait.h>   // needed for waitpid()

#define PROMPT "[ECE340] $ " // Custom Shell Prompt
#define MAX_ARGS   10   // Maximum number of Arguments for argv

int main(void) {
    // Creates an empty array of Strings to hold the arguments for the program.
    char *argv[MAX_ARGS] = {0};
    char input[100]; // will hold user's original input before parsing

    while (1) { // creating an infinite loop that will continuously be prepared for input
        printf(PROMPT); // prints the welcome message/prompt 
        fflush(stdout); // flushing the buffer to print
        
        fgets(input, 100, stdin); // getting input, with max of 100 characters, saving into input

        // before parsing, need to remove \n at the end of the string and replace it
        // this could cause \n to be added to argsv, which should not happen since it's not a valid argument

        // if the input is not empty, this should be checked
        int len_input = strlen(input);
        if (len_input > 0 && input[len_input - 1] == '\n') {
            input[len_input - 1] = '\0'; // replaces \n with \0
        }        

        // if there is no input, repeat the loop (like if user presses enter)
        int trim_len = strlen(input);
        if (trim_len == 0) {
            continue;
        }

        // keep track of the number of arguments input by user
        int num_args = 0;

        // separating the input by spaces, getting the first one
        char* token = strtok(input, " ");

        while (token != NULL && num_args < MAX_ARGS) {
            argv[num_args] = token; // enters single argument into argsv
            token = strtok(NULL, " "); // look for next argument if it exists
            num_args += 1; // increment number of arguments in argsv
        }

        // once all arguments are put into argsv, set last one to NULL to tell OS there are no more
        argv[num_args] = NULL;

        // now, we use a fork to execute the actual arguments given by the user and then print an exit message
        pid_t pid = fork();
        
        if (pid == 0) {
            // enter the child process: executes programs

            // 1. handle the absolute path, running command as is 
            execvp(argv[0], argv); // uses inputted arguments to run executable


            // 2. handle the relative path (with ./)
            char path_relative[100] = "./"; // relative path should include ./ at the beginning

            // now, we can add the name of the program to this, then retry running the program
            // using strncat, we can add the program name to our path string

            // to avoid an error, we must calculate the max number of chracters that can be added to path
            int max_chars_rel = 100 - strlen(path_relative) - 1; // max length of path - current length - space for null term
            strncat(path_relative, argv[0], max_chars_rel);

            // now, we can use execv to run the executable using the complete path
            execv(path_relative, argv);
            

            // 3. handle unix program
            // similarly to above, we'll be appending the argument to the unix path, seeing if its a valid command
            char path_unix[100] = "/usr/bin/";
            int max_chars_unix = 100 - strlen(path_unix) - 1; // max length of path - current length - space for null term
            strncat(path_unix, argv[0], max_chars_unix);
            execv(path_unix, argv);

            // if none of the above work when running program, print error
            printf("Program Not Found\n");
            exit(1);


        } else { 
            // enter the parent process: prints out two messages depending on how child exited
            int child_status = 0;
            
            // wait for child to finish, changes the status to tell us what state child is in
            waitpid(pid, &child_status, 0);

            if (WIFEXITED(child_status)) { // occurs when child is terminated normally
                int return_code = WEXITSTATUS(child_status); // gets exit/return code of process

                // now, we can print the process number and the exit code after the child has finished 
                printf("[Process %d has exited normally with exit code %d]\n", pid, return_code);
            }
            else if (WIFSIGNALED(child_status)) { // occurs when process killed with signal
                int signal = WTERMSIG(child_status); // getting signal number that killed process

                // now, print process and signal that terminated it
                printf("[Process %d was terminated by signal number %d.]\n", pid, signal);
            } 
        }
    }
    return 0; // end!
}