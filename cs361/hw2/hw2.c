#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

#include "sys/types.h"
#include "sys/wait.h"
#include "sys/resource.h"

#define MAX_LINE_LEN 255
#define MAX_ARGS 50

int sh_process(int argc, char **argv)
{
        // if argv[0] is 'exit', then return 0
        if (strncmp(argv[0], "exit", 4) == 0) { return 254; }

        // fork and run process
        pid_t pid = fork();
        int status;

        if (pid) {
                // parent
                printf("forked child, pid=%i\n", pid);
                int* status_ptr = malloc(sizeof *status_ptr);
                struct rusage *ru = malloc(sizeof *ru);
                wait4(pid, status_ptr, 0, ru);
                status = *status_ptr;
                // TODO: report why child ended!
                printf("status => %i\n", status);
                printf("WIFEXITED(status) => %i\n", WIFEXITED(status));
                printf("ru_minflt => %ld\n", ru->ru_minflt);
                printf("ru_majflt => %ld\n", ru->ru_majflt);
                printf("ru_nsignals => %ld\n", ru->ru_nsignals);
                free(status_ptr);
                free(ru);
        } else {
                // child
                status = execvp(argv[0], argv);
                exit(0);
        }
        return status; // only parent should get here
}

void hw2sh()
{
        char *line = malloc(sizeof *line * MAX_LINE_LEN);
        char *tokptr;
        char **args = malloc(sizeof **args * (MAX_ARGS+1)); // need null terminator
        // *(args + MAX_ARGS) = 0; // setting null terminator
        int status;
        int i;
        do {
                printf("$ ");
                line = fgets(line, MAX_LINE_LEN, stdin);
                char *tmp = line;
                while (*tmp) {
                        if (*tmp == '\n') {
                                *tmp = 0;
                                break;
                        }
                        tmp++;
                }
                i = 0;
                tokptr = line;
                while ((args[i] = strtok(tokptr, " ")) != 0) {
                        i++;
                        tokptr=0;
                        if (i >= MAX_ARGS) { break; }
                }
                args[i] = 0;
                status = sh_process(i, args);
        } while (status != 254);
        free(line);
        free(args);
}

int main(int argc, char **argv)
{
        hw2sh();
        return 0;
}
