#include <stdio.h>
#include "budget.h"

#define MAX_DEPARTMENTS 10

void budgetManagement(void)
{
    char department[MAX_DEPARTMENTS][50];
    float allocatedBudget[MAX_DEPARTMENTS];
    float expenditure[MAX_DEPARTMENTS];
    float remainingBudget[MAX_DEPARTMENTS];

    int numberOfDepartments;
    int i;

    printf("\n========================================\n");
    printf("          BUDGET MANAGEMENT\n");
    printf("========================================\n");

    /* Enter number of departments */
    do
    {
        printf("Enter number of departments (1-%d): ", MAX_DEPARTMENTS);
        scanf("%d", &numberOfDepartments);

        if (numberOfDepartments < 1 || numberOfDepartments > MAX_DEPARTMENTS)
        {
            printf("Invalid number. Please try again.\n");
        }

    } while (numberOfDepartments < 1 || numberOfDepartments > MAX_DEPARTMENTS);


    /* Enter budget information */
    for (i = 0; i < numberOfDepartments; i++)
    {
        printf("\n--- Department %d ---\n", i + 1);

        printf("Enter department name: ");
        scanf("%49s", department[i]);

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


        /* Calculate remaining budget */
        remainingBudget[i] =
            allocatedBudget[i] - expenditure[i];
    }


    /* Display budget information */
    printf("\n========================================\n");
    printf("           BUDGET INFORMATION\n");
    printf("========================================\n");

    for (i = 0; i < numberOfDepartments; i++)
    {
        printf("\nDepartment: %s\n", department[i]);
        printf("Allocated Budget: N$%.2f\n",
               allocatedBudget[i]);
        printf("Expenditure: N$%.2f\n",
               expenditure[i]);
        printf("Remaining Budget: N$%.2f\n",
               remainingBudget[i]);

        if (expenditure[i] <= allocatedBudget[i])
        {
            printf("Status: WITHIN BUDGET\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }


    /* Display departments that exceeded their budget */
    printf("\n========================================\n");
    printf("       DEPARTMENTS OVER BUDGET\n");
    printf("========================================\n");

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
