#include <stdio.h>
#include <string.h>

void saveStudentDetails(FILE *file,FILE *namescal) {
    char name[100];
    char address[100];
    char number[10];

    printf("\n\nEnter a name: ");
    gets(name);
    name[strcspn(name, "\n")] = '\0';  // Remove trailing newline, if any

    printf("Enter an address: ");
    gets(address);
    address[strcspn(address, "\n")] = '\0';  // Remove trailing newline, if any

    printf("Enter a Telephone number: ");
    gets(number);
    number[strcspn(number, "\n")] = '\0';  // Remove trailing newline, if any

    // Write student details to the file
    fprintf(file, "Name: %s\nAddress: %s\nTelephone Number: %s\n\n", name, address, number);
    fprintf(namescal,"%s\n",name);

}

void saveStudentInformation(int stunum) {
    FILE *namesfile = fopen("names.txt", "a");
    FILE *namescal = fopen("namesforcal.txt","a");

    if (namesfile == NULL) {
        fprintf(stderr, "Could not open names.txt for writing.\n");
        return;
    }

    for (int i = 0; i < stunum; i++) {
        saveStudentDetails(namesfile,namescal);
    }

    fclose(namesfile);
    printf("\n****INFORMATION SAVED SUCCESSFULLY****\n");
}

void displayStudentInformation() {
    FILE *namesfile = fopen("names.txt", "r");
    if (namesfile == NULL) {
        fprintf(stderr, "Could not open names.txt for reading.\n");
        return;
    }

    printf("\n****STUDENT DETAILS****\n");
    char ch;
    while ((ch = fgetc(namesfile)) != EOF) {
        putchar(ch);
    }

    fclose(namesfile);
}

void erasedata()
    {
    FILE *namesfile = fopen("names.txt", "w");
    FILE *namescal = fopen("namesforcal.txt", "w");
    printf("    Data erased succesfully!!!");
    fclose(namesfile);
    }

int main() {
    int stunum;
    int dataOption;

    printf("******WELCOME TO THE STUDENT REGISTRATION SYSTEM******\n");
    printf("1.Add new student\n2.view student information\n3.Erase all data\nselect an option(1 2 or 3) :");
    scanf("%d",&dataOption);

    switch(dataOption)
    {
    case 1:
        {
          printf("Enter number of students: ");
          scanf("%d", &stunum);
          getchar();  // Consume the newline character left in the input buffer

          saveStudentInformation(stunum);

          displayStudentInformation();
        }
        break;
    case 2:
        {
            displayStudentInformation();
        }
        break;
    case 3:
        {
          erasedata();//erase all data by opening file in write mode
        }
    default :
        {
            printf("invalid selection");
        }
    }
    return 0;
}
