#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define N 4
int print = 0;
int m_sig;
void int_handler(int sig) {
    print = 1;
    m_sig = sig;
}

int main( void ) {
    pid_t pid[N];
    int i, child_status;
    signal(SIGINT, int_handler);
    for (i = 0; i < N; i++)
        if ((pid[i] = fork()) == 0) {
            while(1){ // child infinite loop
                if(print){
                        printf("Process %d received signal %d\n", getpid(), m_sig);
                        exit(0);
                }
            }
        }
    for (i = 0; i < N; i++) {
        printf("Killing process %d\n", pid[i]);
        kill(pid[i], SIGINT);
    }
    for (i = 0; i < N; i++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status))
            printf("Child %d terminated with exit status %d\n",
                   wpid, WEXITSTATUS(child_status));
        else
            printf("Child %d terminated abnormally\n", wpid);
    }
}
