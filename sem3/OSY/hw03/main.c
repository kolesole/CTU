#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "help_sigterm.h"

int main() {
    //creating array for pipe file descriptors
    int f_p[2];
    if (pipe(f_p) < 0) {
        fprintf(stderr, "Error: pipe failed!\n");
        exit(2);
    }
    //creating first process
    const pid_t gen_pid = fork();
    if (gen_pid < 0) {
        fprintf(stderr, "Error: fork GEN failed!\n");
        exit(2);
    }

    if (gen_pid == 0) {
        //closing pipes read
        if (close(f_p[0]) < 0) {
            fprintf(stderr, "Error: close failed!\n");
            exit(2);
        }
        //redirecting stdout to pipes write
        if (dup2(f_p[1], 1) < 0) {
            fprintf(stderr, "Error: dup2 failed!\n");
            exit(2);
        }
        //closing pipes read
        if (close(f_p[1]) < 0) {
            fprintf(stderr, "Error: close failed!\n");
            exit(2);
        }
        //signal setup to end process
        if (signal(SIGTERM, help_sigterm) == SIG_ERR) {
            fprintf(stderr, "Error: signal failed!\n");
            exit(2);
        }

        while (1) {
            //sending two random numbers %4096 to the pipe
            printf("%d %d\n", rand() % 4096, rand() % 4096);
            //assurance that the output is sent immediately
            fflush(stdout);
            sleep(1);
        }
    }
    //creating second process
    const pid_t nsd_pid = fork();
    if (nsd_pid < 0) {
        fprintf(stderr, "Error: fork GEN failed!\n");
        exit(2);
    }

    if (nsd_pid == 0) {
        //closing pipes write
        if (close(f_p[1]) < 0) {
            fprintf(stderr, "Error: close failed!\n");
            exit(2);
        }
        //redirecting stdin to pipes read
        if (dup2(f_p[0], 0) < 0) {
            fprintf(stderr, "Error: dup2 failed!\n");
            exit(2);
        }
        //closing pipes read
        if (close(f_p[0]) < 0) {
            fprintf(stderr, "Error: close failed!\n");
            exit(2);
        }
        //starting nsd program
        execl("./nsd", "nsd", NULL);

        fprintf(stderr, "Error: execl failed!\n");
        exit(2);
    }
    //closing pipes read to avoid collision
    if (close(f_p[0]) < 0) {
        fprintf(stderr, "Error: close failed!\n");
        exit(2);
    }
    //closing pipes write to avoid collision
    if (close(f_p[1]) < 0) {
        fprintf(stderr, "Error: close failed!\n");
        exit(2);
    }

    sleep(5);
    //sending a signal for the first process to be terminated
    if (kill(gen_pid, SIGTERM) < 0) {
        fprintf(stderr, "Error: kill failed!\n");
        exit(2);
    }
    //waiting for the first process to finish
    int gen_status;
    if (wait(&gen_status) < 0) {
        fprintf(stderr, "Error: wait GEN failed!\n");
        exit(2);
    }
    //waiting for the second process to finish
    int nsd_status;
    if (wait(&nsd_status) < 0) {
        fprintf(stderr, "Error: wait NSD failed!\n");
        exit(2);
    }
    //checking if there were any errors in the processes
    if (WIFEXITED(gen_status) && WEXITSTATUS(gen_status) == 0 &&
        WIFEXITED(nsd_status) && WEXITSTATUS(nsd_status) == 0) {
        printf("OK\n");
        exit(0);
    } else {
        printf("ERROR\n");
        exit(1);
    }
}
