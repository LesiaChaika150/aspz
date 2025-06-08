#include <stdio.h>

void grow_stack() {
    int arr1[10000];
    int arr2[10000] = {1};

    printf("Stack inside grow_stack: %p\n", (void *)&arr1);
}

int main() {
    int i;
    printf("Initial stack address:   %p\n", (void *)&i);
    grow_stack();
    return 0;
}
