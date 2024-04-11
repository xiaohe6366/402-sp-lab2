#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "employee.h"
#include "readfile.h"

#define MAX_EMPLOYEES 1024

void print_menu();
int handle_user_choice(int choice, struct employee employees[], int* num_employees);
void load_employee_data(const char* filename, struct employee employees[], int* num_employees);
void sort_employees(struct employee employees[], int num_employees);
void print_database(struct employee employees[], int num_employees);
void lookup_by_id(struct employee employees[], int num_employees);
void lookup_by_last_name(struct employee employees[], int num_employees);
void add_employee(struct employee employees[], int* num_employees);
void remove_employee(struct employee employees[], int* num_employees);
void update_employee(struct employee employees[], int num_employees);
void find_by_first_name(struct employee employees[], int num_employees);
void print_lowest_salaries(struct employee employees[], int num_employees);

int compare_salaries_desc(const void *a, const void *b);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct employee employees[MAX_EMPLOYEES];
    int num_employees = 0;
    
    load_employee_data(argv[1], employees, &num_employees);
    sort_employees(employees, num_employees); // Sort after loading

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);
    } while (handle_user_choice(choice, employees, &num_employees) != 5);

    return 0;
}

void print_menu() {
    printf("\nEmployee Database Menu:\n");
    printf("1. Print the Database\n");
    printf("2. Lookup employee by ID\n");
    printf("3. Lookup employee by last name\n");
    printf("4. Add an Employee\n");
    printf("5. Quit\n");
    printf("6. Remove an Employee\n");
    printf("7. Update an Employee's Information\n");
    printf("8. Print the M employees with the highest salaries\n");
    printf("9. Find all employees with matching last name\n");
    printf("Enter your choice: ");
}

void print_database(struct employee employees[], int num_employees) {
    printf("\nID\tFirst Name\tLast Name\tSalary\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < num_employees; i++) {
        printf("%d\t%s\t\t%s\t\t%d\n", 
            employees[i].id, 
            employees[i].first_name, 
            employees[i].last_name, 
            employees[i].salary);
    }
    printf("-----------------------------------------------------\n");
    printf("Total Employees: %d\n\n", num_employees);
}

void lookup_by_id(struct employee employees[], int num_employees) {
    int id;
    printf("Enter employee ID: ");
    scanf("%d", &id);
    
    for (int i = 0; i < num_employees; i++) {
        if (employees[i].id == id) {
            printf("Employee Found: %d %s %s %d\n", 
                employees[i].id, employees[i].first_name, 
                employees[i].last_name, employees[i].salary);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

void lookup_by_last_name(struct employee employees[], int num_employees) {
    char last_name[MAXNAME];
    printf("Enter employee's last name: ");
    scanf("%63s", last_name);
    
    for (int i = 0; i < num_employees; i++) {
        if (strcasecmp(employees[i].last_name, last_name) == 0) {
            printf("Employee Found: %d %s %s %d\n", 
                employees[i].id, employees[i].first_name, 
                employees[i].last_name, employees[i].salary);
            return;
        }
    }
    printf("Employee with last name %s not found.\n", last_name);
}

void add_employee(struct employee employees[], int* num_employees) {
    if (*num_employees >= MAX_EMPLOYEES) {
        printf("Database is full. Cannot add more employees.\n");
        return;
    }
    
    struct employee new_emp;
    printf("Enter new employee details (ID First_name Last_name Salary): ");
    scanf("%d %63s %63s %d", &new_emp.id, new_emp.first_name, new_emp.last_name, &new_emp.salary);
    
    employees[*num_employees] = new_emp;
    (*num_employees)++;
    sort_employees(employees, *num_employees); // Re-sort after adding
    printf("Employee added successfully.\n");
}

void remove_employee(struct employee employees[], int* num_employees) {
    int id, index = -1;
    printf("Enter employee ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < *num_employees; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        char confirm;
        printf("Are you sure you want to remove this employee (Y/N)? ");
        scanf(" %c", &confirm);  // Note the space before %c to skip any leftover newline characters
        if (confirm == 'Y' || confirm == 'y') {
            for (int i = index; i < *num_employees - 1; i++) {
                employees[i] = employees[i + 1]; // Shift array elements down
            }
            (*num_employees)--;
            printf("Employee removed successfully.\n");
        } else {
            printf("Removal canceled.\n");
        }
    } else {
        printf("Employee not found.\n");
    }
}

void update_employee(struct employee employees[], int num_employees) {
    int id, index = -1;
    printf("Enter employee ID: ");
    scanf("%d", &id);
    for (int i = 0; i < num_employees; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        printf("Found Employee: %d %s %s %d\n",
            employees[index].id, employees[index].first_name, 
            employees[index].last_name, employees[index].salary);

        printf("Enter new first name (or . to keep): ");
        char first_name[MAXNAME];
        scanf("%s", first_name);
        if (strcmp(first_name, ".") != 0) strcpy(employees[index].first_name, first_name);

        printf("Enter new last name (or . to keep): ");
        char last_name[MAXNAME];
        scanf("%s", last_name);
        if (strcmp(last_name, ".") != 0) strcpy(employees[index].last_name, last_name);

        printf("Enter new salary (or -1 to keep): ");
        int salary;
        scanf("%d", &salary);
        if (salary != -1) employees[index].salary = salary;
    } else {
        printf("Employee not found.\n");
    }
}

void find_by_last_name(struct employee employees[], int num_employees) {
    char last_name[MAXNAME];
    printf("Enter the last name to search: ");
    scanf("%63s", last_name);
    printf("Matching Employees:\n");
    for (int i = 0; i < num_employees; i++) {
        if (strcasecmp(employees[i].last_name, last_name) == 0) {
            printf("%d %s %s %d\n", employees[i].id, employees[i].first_name, employees[i].last_name, employees[i].salary);
        }
    }
}

void print_highest_salaries(struct employee employees[], int num_employees) {
    int m;
    printf("Enter the number of employees to display with the highest salaries: ");
    scanf("%d", &m);
    if (m > num_employees) m = num_employees;

    struct employee *temp = malloc(sizeof(struct employee) * num_employees);
    memcpy(temp, employees, sizeof(struct employee) * num_employees);
    qsort(temp, num_employees, sizeof(struct employee), compare_salaries_desc);

    printf("\nEmployees with the highest salaries:\n");
    for (int i = 0; i < m; i++) {
        printf("%d %s %s %d\n", temp[i].id, temp[i].first_name, temp[i].last_name, temp[i].salary);
    }
    free(temp);
}


int compare_salaries_desc(const void *a, const void *b) {
    const struct employee *emp1 = (const struct employee *)a;
    const struct employee *emp2 = (const struct employee *)b;
    return emp2->salary - emp1->salary; // Sort in descending order based on salary
}


int compare_employees(const void *a, const void *b) {
    const struct employee *emp1 = (const struct employee *)a;
    const struct employee *emp2 = (const struct employee *)b;
    return emp1->id - emp2->id;
}

int compare_salaries(const void *a, const void *b) {
    const struct employee *emp1 = (const struct employee *)a;
    const struct employee *emp2 = (const struct employee *)b;
    return emp1->salary - emp2->salary;
}

void sort_employees(struct employee employees[], int num_employees) {
    qsort(employees, num_employees, sizeof(struct employee), compare_employees);
}

void load_employee_data(const char* filename, struct employee employees[], int* num_employees) {
    if (open_file(filename) != 0) {
        printf("Error opening file.\n");
        return;
    }

    while (*num_employees < MAX_EMPLOYEES &&
        read_int(&employees[*num_employees].id) == 0 &&
        read_string(employees[*num_employees].first_name) == 0 &&
        read_string(employees[*num_employees].last_name) == 0 &&
        read_int(&employees[*num_employees].salary) == 0) {
        (*num_employees)++;
    }

    close_file();
}

int handle_user_choice(int choice, struct employee employees[], int* num_employees) {
    switch (choice) {
        case 1:
            print_database(employees, *num_employees); 
            break;
        case 2:
            lookup_by_id(employees, *num_employees); 
            break;
        case 3:
            lookup_by_last_name(employees, *num_employees); 
            break;
        case 4:
            add_employee(employees, num_employees);
            break;
        case 5:
            printf("Quitting program.\n");
            return 5; // Ensure we exit the main loop
        case 6:
            remove_employee(employees, num_employees);
            break;
        case 7:
            update_employee(employees, *num_employees);
            break;
        case 8:
            print_highest_salaries(employees, *num_employees);  // Updated function call
            break;
        case 9:
            find_by_last_name(employees, *num_employees);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
    return 0;
}
