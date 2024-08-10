#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100

// Function for saving student details
void saveStudentDetails(FILE *file, FILE *namescal) {
    char name[100];
    char address[100];
    char number[10];

    printf("\n\nEnter a name: ");
    gets(name);

    printf("Enter an address: ");
    gets(address);

    printf("Enter a Telephone number: ");
    gets(number);

    // Write student details to the file
    fprintf(file, "Name: %s\nAddress: %s\nTelephone Number: %s\n\n", name, address, number);
    fprintf(namescal,"%s\n",name);
}

void saveStudentInformation(int stunum) {
    FILE *namesfile = fopen("names.txt", "a");
    FILE *namescal = fopen("namesforcal.txt","a");

    if (namesfile == NULL || namescal == NULL) {
        printf("Could not open one or more files for writing.\n");
        return;
    }

    for (int i = 0; i < stunum; i++) {
        saveStudentDetails(namesfile,namescal);
    }

    fclose(namesfile);
    fclose(namescal);
    printf("\n****INFORMATION SAVED SUCCESSFULLY****\n");
}

// Function for displaying student information
void displayStudentInformation() {
    FILE *namesfile = fopen("names.txt", "r");
    if (namesfile == NULL) {
        printf("Could not open names.txt for reading.\n");
        return;
    }

    printf("\n****STUDENT DETAILS****\n");

    char names[MAX_STUDENTS][MAX_NAME_LENGTH];
    int numStudents = 0;

    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        if (fgets(names[i], sizeof(names[i]), namesfile) == NULL)
            break;

        numStudents++;
    }

    fclose(namesfile);

    // Display the names
    for (int i = 0; i < numStudents; i++) {
        printf("%s\n", names[i]);
    }
}




// Function for erasing data
void eraseData() {
    FILE *namesfile = fopen("names.txt", "w");
    FILE *namescal = fopen("namesforcal.txt", "w");
    if (namesfile == NULL || namescal == NULL) {
        printf("Could not open one or more files for erasing data.\n");
        return;
    }

    printf("Data erased successfully!\n");

    fclose(namesfile);
    fclose(namescal);
}

// Function for the student registration system
void studentRegSystem() {
    int stunum;
    int dataOption;

    printf("******WELCOME TO THE STUDENT REGISTRATION SYSTEM******\n");
    printf("1. Add new student\n2. View student information\n3. Erase all data\n4. Main menu\nSelect an option (1, 2, 3, or 4): ");
    scanf("%d", &dataOption);

    switch (dataOption) {
        case 1:
            printf("Enter number of students: ");
            scanf("%d", &stunum);
            getchar();
            saveStudentInformation(stunum);
            displayStudentInformation();
            break;
        case 2:
            displayStudentInformation();
            break;
        case 3:
            eraseData();
            break;
        case 4:
            mainMenu();
            break;
        default:
            printf("Invalid selection\n");
            break;
    }
}

// Function for reading student names for result calculator
void readStudentNames(FILE *file, char names[][100], int num_students) {
    for (int i = 0; i < num_students; i++) {
        if (fgets(names[i], 100, file) == NULL) {
            printf("Error reading names from the file.\n");
            mainMenu();
        }
    }
}

// Function for calculating averages
void calculateAverages(int num_students, char names[][100], int marks[][3], double averages[]) {
    for (int i = 0; i < num_students; i++) {
        printf("Enter marks for %s (3 subjects): ", names[i]);
        scanf("%d %d %d", &marks[i][0], &marks[i][1], &marks[i][2]);

        int total_marks = marks[i][0] + marks[i][1] + marks[i][2];
        averages[i] = (double)total_marks / 3.0;
    }
}


// Function for setting order of positions
void bubbleSortDescending(int num_students, char names[][100], int marks[][3], double averages[]) {
    for (int i = 0; i < num_students; i++) {
        for (int j = 0; j < num_students; j++) {
            if (averages[j] < averages[j + 1])
            {
                // Swap averages
                double tempAvg = averages[j];
                averages[j] = averages[j + 1];
                averages[j + 1] = tempAvg;

                // Swap marks
                for (int k = 0; k < 3; k++) {
                    int tempMark = marks[j][k];
                    marks[j][k] = marks[j + 1][k];
                    marks[j + 1][k] = tempMark;
                }

                // Swap names
                char tempName[MAX_NAME_LENGTH];
                for (int k = 0; k < MAX_NAME_LENGTH; k++) {
                    tempName[k] = names[j][k];
                    names[j][k] = names[j + 1][k];
                    names[j + 1][k] = tempName[k];
                }
            }
        }
    }
}


// Function for printing results
void printSortedResults(int num_students, char names[][100], int marks[][3], double averages[]) {
    printf("\n********Student Names, Marks, Averages, and Positions:\n\n\n");
    for (int i = 0; i < num_students; i++) {
        printf("Student: %s\n", names[i]);
        printf("Marks: %d %d %d\n", marks[i][0], marks[i][1], marks[i][2]);
        printf("Average: %.2lf\n", averages[i]);
        printf("Position: %d\n", i + 1);
        printf("\n");
    }
}

// Function to calculate attendance percentage
double calculatePercentage(int attended, int total) {
    return (double)attended / total * 100;
}

// Function for the attendance calculation system

void attendanceCalcSystem() {
    int totalDays;
    char studentNames[100][MAX_NAME_LENGTH];
    int attendance[100];
    int numStudents = 0;

    FILE *file = fopen("namesforcal.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    printf("Enter the total number of days the school held: ");
    scanf("%d", &totalDays);

    // Read student names from the file and store them in arrays
    for (int i = 0; i < 100; i++) {
        if (fgets(studentNames[i], sizeof(studentNames[i]), file) == NULL) {
            break;
        }

        printf("Enter the number of days attended by %s: ", studentNames[i]);
        scanf("%d", &attendance[i]);
        numStudents++;
    }

    // Calculate and display attendance percentages
    printf("\nAttendance Percentages:\n");
    for (int i = 0; i < numStudents; i++) {
        double percentage = calculatePercentage(attendance[i], totalDays);
        printf("%s: %.2lf%%\n", studentNames[i], percentage);
    }

    fclose(file);
}

// Function for the result calculation system
void resultCalcSystem() {
    FILE *file = fopen("namesforcal.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
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
    printSortedResults(num_students, names, marks, averages);

    fclose(file);
}

// Function for the main menu
void mainMenu() {
    int menu;

    printf("\n***********WELCOME TO THE TERM TEST RESULT CALCULATOR AND STUDENT MANAGEMENT SYSTEM***************");

    while (1) {
        printf("\n\n1. Student registration system\n2. Result calculation system\n3. Attendance calculator\n4. Exit\nSelect an option (1, 2, 3, or 4): ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                studentRegSystem();
                break;
            case 2:
                resultCalcSystem();
                break;
            case 3:
                attendanceCalcSystem();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid selection\n");
                mainMenu();
                break;
        }
    }
}

// Main function
int main() {
    mainMenu();
    return 0;
}
