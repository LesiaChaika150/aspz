#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void signal_handler(int sig) {
    printf("[Thread %lu] Отримано сигнал %d\n", (unsigned long)pthread_self(), sig);
}

void* worker(void* arg) {
    // нескінченне очікування сигналу
    while (1) {
        pause();  // чекає на сигнал
    }
    return NULL;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    // Створюємо 3 потоки
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    sleep(1);  // даємо воркерам час на запуск

    // Надсилаємо сигнал кожному потоку
    for (int i = 0; i < 3; i++) {
        pthread_kill(threads[i], SIGUSR1);
    }

    sleep(2);
    printf("Готово. Завершуємо.\n");
    return 0;
}
