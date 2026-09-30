#include <stdio.h>

void displayMenu(){
    printf("\n=======================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

int  main( void ) {
    int choice;
    do {
        displayMenu();
        printf("Please enter your desired choice:");
        scanf("%d", &choice);
        switch(choice){
            case 1: printf("Employee Management- not coded yet\n"); break;
            case 2: printf("Budget Management- not coded yet\n"); break;
            case 3: printf("Supplier Management- not coded yet\n"); break;
            case 4: printf("Asset Management- not coded yet\n"); break;
            case 5: printf("Reports- not coded yet\n"); break;
            case 6: printf("bye-bye!\n"); break;
        }
    }
    while (choice != 6);
    return 0;
}