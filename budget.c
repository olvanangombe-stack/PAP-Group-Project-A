#include <stdio.h>
#include <string.h>
#include "budget.h"

char department[MAX_DEPARTMENTS][50];
float allocatedBudget[MAX_DEPARTMENTS];
float expenditure[MAX_DEPARTMENTS];
float remainingBudget[MAX_DEPARTMENTS];
int numberOfDepartments = 0;

void budgetManagement(void)
{
    int i;

    printf("\n========================================\n");
    printf("          BUDGET MANAGEMENT\n");
    printf("========================================\n");

    do
    {
        printf("Enter number of departments (1-%d): ", MAX_DEPARTMENTS);
        scanf("%d", &numberOfDepartments);

        if (numberOfDepartments < 1 || numberOfDepartments > MAX_DEPARTMENTS)
        {
            printf("Invalid number. Please try again.\n");
        }

    } while (numberOfDepartments < 1 || numberOfDepartments > MAX_DEPARTMENTS);

    for (i = 0; i < numberOfDepartments; i++)
    {
        printf("\n--- Department %d ---\n", i + 1);

        do
        {
            printf("Enter department name: ");
            scanf("%49s", department[i]);

            if (strlen(department[i]) == 0)
            {
                printf("Department name cannot be empty.\n");
            }
        } while (strlen(department[i]) == 0);

        do
        {
            printf("Enter allocated budget: N$");
            scanf("%f", &allocatedBudget[i]);

            if (allocatedBudget[i] < 0)
            {
                printf("Budget cannot be negative.\n");
            }

        } while (allocatedBudget[i] < 0);

        do
        {
            printf("Enter expenditure: N$");
            scanf("%f", &expenditure[i]);

            if (expenditure[i] < 0)
            {
                printf("Expenditure cannot be negative.\n");
            }

        } while (expenditure[i] < 0);

        remainingBudget[i] = allocatedBudget[i] - expenditure[i];
    }

    printf("\n========================================\n");
    printf("           BUDGET INFORMATION\n");
    printf("========================================\n");

    for (i = 0; i < numberOfDepartments; i++)
    {
        printf("\nDepartment: %s\n", department[i]);
        printf("Allocated Budget: N$%.2f\n", allocatedBudget[i]);
        printf("Expenditure: N$%.2f\n", expenditure[i]);
        printf("Remaining Budget: N$%.2f\n", remainingBudget[i]);

        if (expenditure[i] <= allocatedBudget[i])
        {
            printf("Status: WITHIN BUDGET\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }

    printf("\n========================================\n");
    printf("       DEPARTMENTS OVER BUDGET\n");
    printf("========================================\n");

    {
        int foundOverBudget = 0;

        for (i = 0; i < numberOfDepartments; i++)
        {
            if (expenditure[i] > allocatedBudget[i])
            {
                printf("%s exceeded its budget by N$%.2f\n",
                       department[i],
                       expenditure[i] - allocatedBudget[i]);

                foundOverBudget = 1;
            }
        }

        if (foundOverBudget == 0)
        {
            printf("No departments have exceeded their budget.\n");
        }
    }
}
