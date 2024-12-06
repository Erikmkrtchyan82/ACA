#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    
    int ret = fork();
    
    // child process 1
    if (ret == 0) {
        int err = execl("/usr/bin/echo", "echo", "Hello from the child process", NULL);
        if (err == -1) {
            perror("execl");
        }
    }
    // parent process
    else {
        printf("Parent process done\n");
    }

    return 0;
}
