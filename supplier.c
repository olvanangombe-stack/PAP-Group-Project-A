#include <stdio.h>
#include <string.h>
#include "supplier.h"

/* Function to clear the input buffer */
void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear remaining characters */
    }
}

/* Function to add a supplier */
void addSupplier(Supplier suppliers[], int *count)
{
    if (*count >= MAX_SUPPLIERS)
    {
        printf("\nSupplier storage is full.\n");
        return;
    }

    printf("\n========== ADD SUPPLIER ==========\n");

    printf("Enter Supplier ID: ");
    scanf("%d", &suppliers[*count].supplierID);
    clearInputBuffer();

    /* Check for duplicate Supplier ID */
    for (int i = 0; i < *count; i++)
    {
        if (suppliers[i].supplierID == suppliers[*count].supplierID)
        {
            printf("Supplier ID already exists.\n");
            return;
        }
    }

    printf("Enter Supplier Name: ");
    fgets(suppliers[*count].name,
          sizeof(suppliers[*count].name), stdin);

    suppliers[*count].name[
        strcspn(suppliers[*count].name, "\n")
    ] = '\0';

    printf("Enter Email: ");
    fgets(suppliers[*count].email,
          sizeof(suppliers[*count].email), stdin);

    suppliers[*count].email[
        strcspn(suppliers[*count].email, "\n")
    ] = '\0';

    printf("Enter Telephone Number: ");
    fgets(suppliers[*count].telephone,
          sizeof(suppliers[*count].telephone), stdin);

    suppliers[*count].telephone[
        strcspn(suppliers[*count].telephone, "\n")
    ] = '\0';

    printf("Enter Town/Location: ");
    fgets(suppliers[*count].location,
          sizeof(suppliers[*count].location), stdin);

    suppliers[*count].location[
        strcspn(suppliers[*count].location, "\n")
    ] = '\0';

    (*count)++;

    printf("\nSupplier added successfully!\n");
}

/* Function to display all suppliers */
void displaySuppliers(Supplier suppliers[], int count)
{
    if (count == 0)
    {
        printf("\nNo suppliers have been registered.\n");
        return;
    }

    printf("\n================ SUPPLIER LIST ================\n");

    for (int i = 0; i < count; i++)
    {
        printf("\nSupplier %d\n", i + 1);
        printf("-----------------------------------------------\n");
        printf("Supplier ID : %d\n", suppliers[i].supplierID);
        printf("Name        : %s\n", suppliers[i].name);
        printf("Email       : %s\n", suppliers[i].email);
        printf("Telephone   : %s\n", suppliers[i].telephone);
        printf("Location    : %s\n", suppliers[i].location);
    }

    printf("\n===============================================\n");
}

/* Function to search for a supplier by ID */
void searchSupplier(Supplier suppliers[], int count)
{
    int id;
    int found = 0;

    if (count == 0)
    {
        printf("\nNo suppliers have been registered.\n");
        return;
    }

    printf("\n========== SEARCH SUPPLIER ==========\n");

    printf("Enter Supplier ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < count; i++)
    {
        if (suppliers[i].supplierID == id)
        {
            printf("\nSupplier Found!\n");
            printf("--------------------------------\n");
            printf("Supplier ID : %d\n", suppliers[i].supplierID);
            printf("Name        : %s\n", suppliers[i].name);
            printf("Email       : %s\n", suppliers[i].email);
            printf("Telephone   : %s\n", suppliers[i].telephone);
            printf("Location    : %s\n", suppliers[i].location);
            printf("--------------------------------\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nSupplier with ID %d was not found.\n", id);
    }
}

/* Function to compare two suppliers */
void compareSuppliers(Supplier suppliers[], int count)
{
    int id1, id2;
    int index1 = -1;
    int index2 = -1;

    if (count < 2)
    {
        printf("\nAt least two suppliers are required for comparison.\n");
        return;
    }

    printf("\n========== COMPARE SUPPLIERS ==========\n");

    printf("Enter first Supplier ID: ");
    scanf("%d", &id1);

    printf("Enter second Supplier ID: ");
    scanf("%d", &id2);

    clearInputBuffer();

    for (int i = 0; i < count; i++)
    {
        if (suppliers[i].supplierID == id1)
        {
            index1 = i;
        }

        if (suppliers[i].supplierID == id2)
        {
            index2 = i;
        }
    }

    if (index1 == -1 || index2 == -1)
    {
        printf("\nOne or both Supplier IDs were not found.\n");
        return;
    }

    printf("\n=============== SUPPLIER COMPARISON ===============\n");

    printf("\nSupplier 1\n");
    printf("ID        : %d\n", suppliers[index1].supplierID);
    printf("Name      : %s\n", suppliers[index1].name);
    printf("Email     : %s\n", suppliers[index1].email);
    printf("Telephone : %s\n", suppliers[index1].telephone);
    printf("Location  : %s\n", suppliers[index1].location);

    printf("\nSupplier 2\n");
    printf("ID        : %d\n", suppliers[index2].supplierID);
    printf("Name      : %s\n", suppliers[index2].name);
    printf("Email     : %s\n", suppliers[index2].email);
    printf("Telephone : %s\n", suppliers[index2].telephone);
    printf("Location  : %s\n", suppliers[index2].location);

    printf("\n====================================================\n");

    if (strcmp(suppliers[index1].location,
               suppliers[index2].location) == 0)
    {
        printf("Both suppliers are located in the same town/location.\n");
    }
    else
    {
        printf("The suppliers are located in different towns/locations.\n");
    }

    if (strcmp(suppliers[index1].email,
               suppliers[index2].email) == 0)
    {
        printf("Warning: Both suppliers have the same email address.\n");
    }
}

/* Supplier Management Menu */
void supplierMenu(void)
{
    Supplier suppliers[MAX_SUPPLIERS];
    int count = 0;
    int choice;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("       SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare Suppliers\n");
        printf("5. Return to Main Menu\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addSupplier(suppliers, &count);
                break;

            case 2:
                displaySuppliers(suppliers, count);
                break;

            case 3:
                searchSupplier(suppliers, count);
                break;

            case 4:
                compareSuppliers(suppliers, count);
                break;

            case 5:
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 5);
}

