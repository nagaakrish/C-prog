#include <stdio.h>
#include "functions.h" 

int main() {
    const char *filename = "Ajima_Physical_Fitness_Members.txt"; 
    int choice;

    do {
        printf("\n Ajima Physical Fitness Membership Management \n");
        printf("1. Add a new payment record\n");
        printf("2. Display all payment records\n");
        printf("3. Delete a payment record\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMember(filename);
                break;
            case 2:
                displayMembers(filename);
                break;
            case 3:
                deleteMember(filename);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
