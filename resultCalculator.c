#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//function for reading data from file
void readStudentNames(FILE *file, char names[][100], int num_students) {
    for (int i = 0; i < num_students; i++) {
        if (fgets(names[i], 100, file) == NULL) {
            printf("Error reading names from the file.\n");
            exit(1);


        }
    }
}
//function for calculate avarages
void calculateAverages(int num_students, char names[][100], int marks[][3], double averages[]) {
    for (int i = 0; i < num_students; i++) {
        printf("Enter marks for %s (3 subjects): ", names[i]);
        scanf("%d %d %d", &marks[i][0], &marks[i][1], &marks[i][2]);

        int total_marks = marks[i][0] + marks[i][1] + marks[i][2];
        averages[i] = (double)total_marks / 3.0;
    }
}
//function for display results
void displayResults(int num_students, char names[][100], int marks[][3], double averages[]) {
    printf("\nStudent Names, Marks, and Averages:\n");
    for (int i = 0; i < num_students; i++) {
        printf("Student: %s\n", names[i]);
        printf("Marks: %d %d %d\n", marks[i][0], marks[i][1], marks[i][2]);
        printf("Average: %.2lf\n", averages[i]);
        printf("\n");
    }
}

void bubbleSortDescending(int num_students, char names[][100], int marks[][3], double averages[]) {
    bool swapped;
    for (int i = 0; i < num_students - 1; i++) {
        swapped = false;
        for (int j = 0; j < num_students - i - 1; j++) {
            if (averages[j] < averages[j + 1]) {
                // Swap averages
                double tempAvg = averages[j];
                averages[j] = averages[j + 1];
                averages[j + 1] = tempAvg;

                // Swap names
                char tempName[100];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                // Swap marks
                int tempMarks[3];
                for (int k = 0; k < 3; k++) {
                    tempMarks[k] = marks[j][k];
                    marks[j][k] = marks[j + 1][k];
                    marks[j + 1][k] = tempMarks[k];
                }

                swapped = true;
            }
        }

        // If no two elements were swapped in inner loop, the array is already sorted
        if (!swapped) {
            break;
        }
    }
}


void printSortedResults(int num_students, char names[][100], int marks[][3], double averages[]) {
    printf("\n********Student Names, Marks, Averages and Position:\n\n\n");
    for (int i = 0; i < num_students; i++) {
        printf("Student: %s\n", names[i]);
        printf("Marks: %d %d %d\n", marks[i][0], marks[i][1], marks[i][2]);
        printf("Average: %.2f\n", averages[i]);
        printf("Position: %d\n", i+1);
        printf("\n");
    }
}
// Function to calculate attendance percentage
double calculatePercentage(int attended, int total)
{
    return (double)attended / total * 100;
}

int main() {
    FILE *file = fopen("namesforcal.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    int num_students;
    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    char names[num_students][100];
    int marks[num_students][3];
    double averages[num_students];

    readStudentNames(file, names, num_students);
    calculateAverages(num_students, names, marks, averages);
    bubbleSortDescending(num_students, names, marks, averages);
    displayResults(num_students, names, marks, averages);
    printSortedResults(num_students, names, marks, averages);

    fclose(file);
    return 0;
}



