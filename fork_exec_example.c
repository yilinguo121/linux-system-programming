#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid;
    printf("Parent process starting (PID: %d)\n", getpid());
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) {
        printf("Child process created (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        printf("Child process executing: ls -la\n");
        execlp("/bin/ls", "ls", "-la", NULL);
        fprintf(stderr, "execlp failed\n");
        exit(1);
    }
    else {
        printf("Parent process waiting for child (Child PID: %d)\n", pid);
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child Complete with exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }
    return 0;
}