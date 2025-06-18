#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void* worker(void* arg) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    // Потік чекає сигнал
    int sig;
    siginfo_t info;
    printf("[Thread %lu] Очікую сигнал SIGUSR1...\n", (unsigned long)pthread_self());

    sig = sigwaitinfo(&set, &info);
    if (sig == SIGUSR1) {
        printf("[Thread %lu] Отримано сигнал SIGUSR1 від PID %d\n", 
               (unsigned long)pthread_self(), info.si_pid);
    }

    return NULL;
}

int main() {
    // Блокуємо SIGUSR1 у головному потоці
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    // Створюємо 3 потоки
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    sleep(1);  // щоб воркери встигли налаштуватися

    // Надсилаємо сигнали кожному воркеру
    for (int i = 0; i < 3; i++) {
        pthread_kill(threads[i], SIGUSR1);
    }

    // Чекаємо завершення потоків
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Усі воркери завершилися. Програма завершена.\n");
    return 0;
}
