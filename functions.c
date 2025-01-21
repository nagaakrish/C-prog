#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void addMember(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char name[50], month[20];
    float payment;

    printf("Enter member's name: ");
    scanf(" %[^\n]", name);
    printf("Enter payment month (e.g., January, February): ");
    scanf(" %[^\n]", month);
    printf("Enter monthly payment: ");
    scanf("%f", &payment);

    fprintf(file, "%s,%s,%.2f\n", name, month, payment);
    printf("Member payment record added successfully!\n");

    fclose(file);
}

void displayMembers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[200];
    printf("\n=== Member Payment Records ===\n");
    printf("Name\t\tMonth\t\tMonthly Payment\n");
    printf("--------------------------------------------\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        char name[50], month[20];
        float payment;

        if (sscanf(line, "%[^,],%[^,],%f", name, month, &payment) == 3) {
            printf("%-15s %-15s $%-10.2f\n", name, month, payment);
        }
    }
    fclose(file);
}

void deleteMember(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char nameToDelete[50], monthToDelete[20];
    printf("Enter the name of the member to delete: ");
    scanf(" %[^\n]", nameToDelete);
    printf("Enter the month of the payment record to delete: ");
    scanf(" %[^\n]", monthToDelete);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    char line[200];
    int recordFound = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char name[50], month[20];
        float payment;

        if (sscanf(line, "%[^,],%[^,],%f", name, month, &payment) == 3) {
            if (strcmp(name, nameToDelete) != 0 || strcmp(month, monthToDelete) != 0) {
                fprintf(tempFile, "%s,%s,%.2f\n", name, month, payment);
            } else {
                recordFound = 1;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);

    if (recordFound) {
        printf("Member payment record for '%s' in month '%s' deleted successfully!\n", nameToDelete, monthToDelete);
    } else {
        printf("No record found for member '%s' in month '%s'.\n", nameToDelete, monthToDelete);
    }
}
