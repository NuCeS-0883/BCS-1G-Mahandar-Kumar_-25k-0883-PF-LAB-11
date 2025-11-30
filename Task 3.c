#include <stdio.h>
#include <string.h>
struct Date {
    int day;
    int month;
    int year;
};
struct Employee {
    int id;
    char name[50];
    char department[20];
    char designation[20];
    float salary;
    char phone[15];
    char email[50];
    struct Date joining_date;
    int years_experience;
};
struct Employee emp[100];
int count = 0;
int calculate_experience(struct Date d) {
    int current_year = 2025;
    return current_year - d.year;
}
void addEmployee() {
    printf("\n--- Add New Employee ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp[count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", emp[count].name);
    printf("Enter Department (IT/HR/Finance/Marketing/Operations): ");
    scanf("%s", emp[count].department);
    printf("Enter Designation (Intern/Junior/Senior/Manager/Director): ");
    scanf("%s", emp[count].designation);
    printf("Enter Salary: ");
    scanf("%f", &emp[count].salary);
    printf("Enter Phone Number: ");
    scanf("%s", emp[count].phone);
    printf("Enter Email: ");
    scanf("%s", emp[count].email);
    printf("Enter Joining Date (DD MM YYYY): ");
    scanf("%d %d %d", &emp[count].joining_date.day,
          &emp[count].joining_date.month,
          &emp[count].joining_date.year);
    emp[count].years_experience =
        calculate_experience(emp[count].joining_date);
    count++;
    printf("\nEmployee Added Successfully!\n");
}

void displayEmployee(struct Employee e) {
    printf("\n----------------------\n");
    printf("ID: %d\n", e.id);
    printf("Name: %s\n", e.name);
    printf("Department: %s\n", e.department);
    printf("Designation: %s\n", e.designation);
    printf("Salary: %.2f\n", e.salary);
    printf("Phone: %s\n", e.phone);
    printf("Email: %s\n", e.email);
    printf("Joining Date: %02d-%02d-%04d\n",
           e.joining_date.day, e.joining_date.month, e.joining_date.year);
    printf("Experience: %d years\n", e.years_experience);
}
void searchByDepartment() {
    char dept[20];
    printf("Enter department to search: ");
    scanf("%s", dept);
    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].department, dept) == 0) {
            displayEmployee(emp[i]);
        }
    }
}
void searchByDesignation() {
    char desig[20];
    printf("Enter designation: ");
    scanf("%s", desig);
    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].designation, desig) == 0) {
            displayEmployee(emp[i]);
        }
    }
}
void searchByExperience() {
    int exp;
    printf("Enter minimum years of experience: ");
    scanf("%d", &exp);
    for (int i = 0; i < count; i++) {
        if (emp[i].years_experience >= exp) {
            displayEmployee(emp[i]);
        }
    }
}
void salaryStatistics() {
    char dept[20];
    printf("Enter department: ");
    scanf("%s", dept);
    float sum = 0;
    int c = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(emp[i].department, dept) == 0) {
            sum += emp[i].salary;
            c++;
        }
    }
    if (c > 0) {
        printf("\nAverage Salary in %s: %.2f\n", dept, sum / c);
    } else {
        printf("No employees found in this department.\n");
    }
}
void annualAppraisal() {
    int id;
    float percent;
    printf("Enter Employee ID: ");
    scanf("%d", &id);
    printf("Enter increment percent (5-15): ");
    scanf("%f", &percent);
    if (percent < 5 || percent > 15) {
        printf("Invalid increment!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        if (emp[i].id == id) {
            float inc = emp[i].salary * (percent / 100);
            emp[i].salary += inc;
            printf("New Salary: %.2f\n", emp[i].salary);
            return;
        }
    }
    printf("Employee not found.\n");
}
void eligibleForPromotion() {
    printf("\nEmployees Eligible for Promotion (>3 years experience):\n");
    for (int i = 0; i < count; i++) {
        if (emp[i].years_experience > 3) {
            displayEmployee(emp[i]);
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n---- Employee Record System ----\n");
        printf("1. Add Employee\n");
        printf("2. Search by Department\n");
        printf("3. Search by Designation\n");
        printf("4. Search by Experience\n");
        printf("5. Salary Statistics (Department-wise)\n");
        printf("6. Annual Appraisal\n");
        printf("7. Promotion Eligibility\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            searchByDepartment();
            break;
        case 3:
            searchByDesignation();
            break;
        case 4:
            searchByExperience();
            break;
        case 5:
            salaryStatistics();
            break;
        case 6:
            annualAppraisal();
            break;
        case 7:
            eligibleForPromotion();
            break;
        case 8:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}


