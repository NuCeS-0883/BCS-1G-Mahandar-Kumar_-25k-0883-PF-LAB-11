#include <stdio.h>
#include <string.h>
struct Marks {
    float sub1;
    float sub2;
    float sub3;
};
struct Student {
    char name[50];
    int roll;
    struct Marks m;
    float percentage;
    char grade[3];
};
void assignGrade(struct Student *s) {
    float p = s->percentage;
    if (p >= 90) strcpy(s->grade, "A+");
    else if (p >= 80) strcpy(s->grade, "A");
    else if (p >= 70) strcpy(s->grade, "B+");
    else if (p >= 60) strcpy(s->grade, "B");
    else if (p >= 50) strcpy(s->grade, "C");
    else strcpy(s->grade, "F");
}
float validMarks() {
    float m;
    do {
        scanf("%f", &m);
        if (m < 0 || m > 100)
            printf("Invalid! Enter marks between 0–100: ");
    } while (m < 0 || m > 100);
    return m;
}
void sortByPercentage(struct Student s[], int n) {
    struct Student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[j].percentage > s[i].percentage) {  
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    struct Student s[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", s[i].name);
        printf("Roll Number: ");
        scanf("%d", &s[i].roll);
        printf("Enter marks in Subject 1 (0-100): ");
        s[i].m.sub1 = validMarks();
        printf("Enter marks in Subject 2 (0-100): ");
        s[i].m.sub2 = validMarks();

        printf("Enter marks in Subject 3 (0-100): ");
        s[i].m.sub3 = validMarks();
        float total = s[i].m.sub1 + s[i].m.sub2 + s[i].m.sub3;
        s[i].percentage = (total / 300.0f) * 100;
        assignGrade(&s[i]);
    }
	 printf("\n\n---------- STUDENT RECORDS ----------\n");
    	for (int i = 0; i < n; i++) {
        printf("\nName: %s\n", s[i].name);
        printf("Roll: %d\n", s[i].roll);
        printf("Marks: %.1f, %.1f, %.1f\n", s[i].m.sub1, s[i].m.sub2, s[i].m.sub3);
        printf("Percentage: %.2f\nGrade: %s\n", s[i].percentage, s[i].grade);
    }
    int choice;
    printf("\nSearch Student By:\n1. Roll Number\n2. Name\nEnter choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        int rollSearch;
        printf("Enter roll number: ");
        scanf("%d", &rollSearch);
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (s[i].roll == rollSearch) {
                printf("\nFOUND!\nName: %s\nRoll: %d\nPercentage: %.2f\nGrade: %s\n",
                       s[i].name, s[i].roll, s[i].percentage, s[i].grade);
                found = 1;
                break;
            }
        }
        if (!found) printf("No record found.\n");

    } else if (choice == 2) {
        char nameSearch[50];
        printf("Enter name: ");
        scanf(" %[^\n]", nameSearch);

        int found = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(s[i].name, nameSearch) == 0) {
                printf("\nFOUND!\nName: %s\nRoll: %d\nPercentage: %.2f\nGrade: %s\n",
                       s[i].name, s[i].roll, s[i].percentage, s[i].grade);
                found = 1;
            }
        }
        if (!found) printf("No record found.\n");
    }
	float sum = 0;
    for (int i = 0; i < n; i++)
        sum += s[i].percentage;
    float average = sum / n;
    printf("\nClass Average = %.2f\n", average);
    printf("\nStudents ABOVE Average:\n");
    for (int i = 0; i < n; i++)
        if (s[i].percentage > average)
            printf("%s (%.2f)\n", s[i].name, s[i].percentage);
    printf("\nStudents BELOW Average:\n");
    for (int i = 0; i < n; i++)
        if (s[i].percentage < average)
            printf("%s (%.2f)\n", s[i].name, s[i].percentage);
    printf("\n\n---------- STUDENT RANKS ----------\n");
    sortByPercentage(s, n);
    for (int i = 0; i < n; i++) {
        printf("Rank %d: %s (%.2f%%)\n", i + 1, s[i].name, s[i].percentage);
    }
    return 0;
}

