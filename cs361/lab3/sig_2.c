#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int counter = 2;
int flag = 0;
void myHandler(int sig) {
  counter++;
  flag = 1; //set to true
}

int main() {
  signal(SIGUSR1, myHandler);
  printf("%d ", counter);
  fflush(stdout);
  int pid = fork();
  if (pid == 0) {
    while(1) {
        if(flag){
                printf("%d ", counter);
                exit(0);
        }
    }
  }
  kill(pid, SIGUSR1);
  waitpid(pid, NULL, 0);
  counter--;
  printf("%d ", counter);
  return 0;
}
