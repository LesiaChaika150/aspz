#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "data.txt"

int main() {
    FILE *fp;

    printf("Перевірка наявності файлу %s...\n", FILENAME);

    fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("Файл не знайдено");
        printf("Спробуйте створити файл вручну та натисніть Enter...\n");
        getchar(); // чекаємо на Enter
    } else {
        printf("Файл знайдено. Читаємо вміст:\n");

        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            printf(">> %s", line);
        }
        fclose(fp);
    }

    // Спроба прочитати файл ще раз
    printf("\nСпробуємо ще раз відкрити файл...\n");
    fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("Знову немає доступу до файлу");
        printf("Спробуйте знову створити файл, потім натисніть Enter...\n");
        getchar();
    } else {
        printf("Файл відновлено. Повторне читання:\n");
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            printf(">> %s", line);
        }
        fclose(fp);
    }

    printf("\nПрограма завершила роботу.\n");
    return 0;
}
