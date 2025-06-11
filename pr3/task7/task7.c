#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void print_limit(int resource, const char* name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == 0) {
        printf("%-20s: soft = %lu, hard = %lu\n", name, 
            (unsigned long)limit.rlim_cur, (unsigned long)limit.rlim_max);
    } else {
        perror("getrlimit");
    }
}

int main() {
    printf("Поточні обмеження ресурсів:\n\n");

    print_limit(RLIMIT_CPU, "CPU time (сек)");
    print_limit(RLIMIT_FSIZE, "Max file size");
    print_limit(RLIMIT_DATA, "Data seg size");
    print_limit(RLIMIT_STACK, "Stack size");
    print_limit(RLIMIT_CORE, "Core file size");
    print_limit(RLIMIT_RSS, "Resident set");
    print_limit(RLIMIT_NOFILE, "Open files");
    print_limit(RLIMIT_AS, "Address space");

    return 0;
}
