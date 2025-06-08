#include <stdio.h>
#include <time.h>


int main() {

    time_t t = (time_t)~0 >> 1;

    printf("Максимальний time_t: %ld\n", (long)t);

    printf("Дата завершення time_t: %s", ctime(&t));

    return 0;

}

