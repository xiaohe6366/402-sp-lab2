#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAXNAME 64

// Employee structure definition
struct employee {
    int id;
    char first_name[MAXNAME];
    char last_name[MAXNAME];
    int salary;
};

// Function declarations for comparing employees
int compare_employees(const void *a, const void *b);
int compare_salaries(const void *a, const void *b);

#endif // EMPLOYEE_H
