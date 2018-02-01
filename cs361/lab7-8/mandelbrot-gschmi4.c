#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "sys/wait.h"
#include "sys/time.h"
#include "sys/resource.h"

int main() {
        int child1 = 0;
        int child2 = 0;
        int pip1[2], pip2[2];
        char buf[20];
        pipe(pip1);
        pipe(pip2);
        int shid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
        int *shptr = (int*)shmat(shid, 0, 0);
        child1 = fork();
        if (child1 == -1) { exit(1); }
        if (child1) {
                child2 = fork();
        }
        if (!child1) {
                // child1
                // write to shid
                shptr[0] = 234;
                // close pip1[1] and pip2[0]; read from pip1[0]
                close(pip1[1]);
                close(pip2[0]);
                read(pip1[0], buf, 10);
                printf("child1: %s\n", buf);
                // send 'child1' to pip2[1]
                write(pip2[1], "child1", 7);
                // close remaining fd's
                close(pip1[0]);
                close(pip2[1]);
                // child1: run mandelcalc
                char *argv[] = { "./mandelcalc-gschmi4", "arg1", 0 };
                execvp(argv[0], argv);
        } else if (!child2) {
                // child2
                // close pip1[0-1] and pip2[1]; read from pip2[0]
                close(pip1[0]);
                close(pip1[1]);
                close(pip2[1]);
                read(pip2[0], buf, 10);
                printf("child2: %s\n", buf);
                // close remaining fd's
                close(pip2[0]);
                // child2: run mandeldisplay
                char *argv[] = { "./mandeldisplay-gschmi4", "arg2", 0 };
                execvp(argv[0], argv);
        } else {
                // close pip1[0] and pip2[0-1]; write 'parent' to pip1[1]
                close(pip1[0]);
                close(pip2[0]);
                close(pip2[1]);
                write(pip1[1], "parent", 7);
                // close remaining fd's
                close(pip1[1]);
                // wait for children and display exit values
                int ret1, ret2;
                waitpid(child1, &ret1, 0);
                waitpid(child2, &ret2, 0);
                printf("Exit codes of child 1 and child 2 are (respectively): %i %i\n", WEXITSTATUS(ret1), WEXITSTATUS(ret2));
                printf("My shared mem space says: %i\n", shptr[0]);
                shmdt(shptr);
                shmctl(shid, IPC_RMID, 0);
        }
        return 0;
}
