#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main() {
    pid_t pid;
    cout << "C++ Fork and Exec Example" << endl;
    cout << "Parent process starting (PID: " << getpid() << ")" << endl;
    pid = fork();
    if (pid < 0) {
        cerr << "Fork Failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        cout << "Child process created (PID: " << getpid() << ", Parent PID: " << getppid() << ")" << endl;
        cout << "Child process executing: ls -la" << endl;
        execlp("ls", "ls", "-la", NULL);
        cerr << "execlp failed" << endl;
        exit(1);
    }
    else {
        cout << "Parent process waiting for child (Child PID: " << pid << ")" << endl;
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            cout << "Child Complete with exit status: " << WEXITSTATUS(status) << endl;
        } else {
            cout << "Child process terminated abnormally" << endl;
        }
    }
    cout << "Process execution completed" << endl;
    return 0;
}
