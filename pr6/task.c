#include <stdio.h>
#include <string.h>

struct Data {
    int id;
    union {
        int age;
        char name[10];
    } info;
    double salary;
};

int main() {
    struct Data employee;

    employee.id = 1;
    employee.info.age = 25;
    employee.salary = 50000.0;

    printf("Перед перезаписом:\n");
    printf("ID: %d\n", employee.id);
    printf("Age: %d\n", employee.info.age);
    printf("Salary: %.2f\n", employee.salary);

    strcpy(employee.info.name, "Alexander");

    printf("\nПісля запису у name:\n");
    printf("ID: %d\n", employee.id);
    printf("Age (перезаписане): %d\n", employee.info.age);
    printf("Name: %s\n", employee.info.name);
    printf("Salary: %.2f\n", employee.salary);

    return 0;
}