#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *my_malloc(size_t size) {
    void *ptr = malloc(size);
    FILE *log = fopen("allocation.log", "a");
    if (log != NULL) {
        time_t now = time(NULL);
        fprintf(log, "Time: %s", ctime(&now));
        fprintf(log, "Allocated %zu bytes at address %p\n", size, ptr);
        fclose(log);
    }
    return ptr;
}

int main() {
    // Приклад виділення різних об’ємів пам’яті
    int *array = (int *)my_malloc(10 * sizeof(int));
    char *string = (char *)my_malloc(50 * sizeof(char));
    double *matrix = (double *)my_malloc(100 * sizeof(double));

    // Робимо якісь операції...
    
    // Звільняємо пам’ять
    free(array);
    free(string);
    free(matrix);

    printf("Memory allocation completed. Check allocation.log for details.\n");
    return 0;
}
