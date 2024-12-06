#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    
    int ret1 = fork();
    
    // child process 1
    if (ret1 == 0) {
        int err = execl("/usr/bin/ls", "ls", NULL);
        if (err == -1) {
            perror("execl 1");
        }
    }
    // parent process
    else {
        int ret2 = fork();
        // child process 2
        if (ret2 == 0) {
            int err = execl("/usr/bin/date", "date", NULL);
            if (err == -1) {
                perror("execl 2");
            }
        }
        // parent process
        else {
            printf("Parent process done\n");
        }
    }

    return 0;
}
