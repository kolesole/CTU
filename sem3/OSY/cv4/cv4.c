#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int f_p[2];
    pipe(f_p);
    pid_t pid = fork();
    if (pid < 0) {exit(1);}
    if (pid == 0) {
        close(f_p[0]);
        dup2(f_p[1], 1);  // Redirect stdout to pipe's write end
        close(f_p[1]);
        printf("aaa\nbbb\nccc\n");  // Send this to the pipe
        return 0;
    } else {
        int pid2 = fork();
        if (pid2 == 0) {
            close(f_p[1]);
            dup2(f_p[0], 0);  // Redirect pipe's read end to stdin
            close(f_p[0]);
            execlp("grep", "grep", "a", NULL);  // Correct arguments for execlp
            printf("ERROR\n");  // This should never run unless execlp fails
            exit(1);
        } else {
            close(f_p[0]);
            close(f_p[1]);
            int status1, status2;
            wait(&status1);  // Wait for both child processes to finish
            wait(&status2);
        }
    }
}
