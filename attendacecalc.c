#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100 // Maximum number of students
#define MAX_NAME_LENGTH 100 // Maximum length of a student's name

// Function to calculate attendance percentage
double calculatePercentage(int attended, int total) {
    return (double)attended / total * 100;
}

int main() {
    int totalDays;
    char studentNames[MAX_STUDENTS][MAX_NAME_LENGTH];
    int attendance[MAX_STUDENTS];
    int numStudents = 0;

    // Open the file containing student names
    FILE *file = fopen("namesforcal.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Input the total number of days
    printf("Enter the total number of days the school held: ");
    scanf("%d", &totalDays);

    // Read student names from the file and store them in arrays
    char line[MAX_NAME_LENGTH];
    while (numStudents < MAX_STUDENTS && fgets(line, sizeof(line), file) != NULL) {
        // Remove the trailing newline character
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(studentNames[numStudents], line);

        printf("Enter the number of days attended by %s: ", studentNames[numStudents]);
        scanf("%d", &attendance[numStudents]);
        numStudents++;
    }



    // Calculate and display attendance percentages for each student
    printf("\nAttendance Percentages:\n");
    for (int i = 0; i < numStudents; i++) {
        double percentage = calculatePercentage(attendance[i], totalDays);
        printf("%s: %.2lf%%\n", studentNames[i], percentage);
    }

    // Close the file
    fclose(file);

    return 0;
}
