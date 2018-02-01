#include "stdlib.h"
#include "stdio.h"
#include "signal.h"
#include "unistd.h"

int su2_once = 0;
int ppid = 0;
int cpid = 0;
int *status;

void su1_handle(int signum) {
        exit(1);
}

void su2_handle(int signum) {
        if (!su2_once) {
                kill(cpid, SIGUSR1);
                wait4(cpid, status, 0, 0);
                su2_once = 1;
        }
}

int main(int argc, char *argv[]) {
        int n = atoi(argv[1]);
        status = malloc(sizeof(*status));
        cpid = fork();
        if (!cpid) {
                // child
                signal(SIGUSR1, su1_handle);
                sleep(n);
                ppid = getppid();
                kill(ppid, SIGUSR2);
                exit(2);
        } else {
                // parent
                signal(SIGUSR2, su2_handle);
                signal(SIGALRM, su2_handle);
                alarm(n);
                while(!su2_once) {}
                printf("child exited -- %i\n", *status);
                free(status);
                char *myargs[] = {"ps", "-e", "-l", "-f", 0};
                int e = execvp("ps", myargs);
                if (e) { exit(-1); }
                exit(0);
        }
        return 0;
}
