#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork error");
            exit(1);
        } else if (pids[i] == 0) {
            // Дочірній процес
            printf("Дочірній процес %d: PID = %d, PPID = %d\n", i + 1, getpid(), getppid());
            sleep(1 + i);  // кожен процес живе трохи довше
            printf("Дочірній процес %d (PID = %d) завершено\n", i + 1, getpid());
            exit(0);
        }
    }

    // Батьківський процес
    int status;
    pid_t ended_pid;

    for (int i = 0; i < 3; i++) {
        ended_pid = wait(&status);
        printf("Батько: дочірній процес з PID %d завершився (код: %d)\n", ended_pid, WEXITSTATUS(status));
    }

    printf("Батьківський процес завершився.\n");

    return 0;
}
