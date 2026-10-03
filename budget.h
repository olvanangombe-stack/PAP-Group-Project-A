#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10

/* These extern lines allow Reports to access the Budget data */
extern char department[MAX_DEPARTMENTS][50];
extern float allocatedBudget[MAX_DEPARTMENTS];
extern float expenditure[MAX_DEPARTMENTS];
extern float remainingBudget[MAX_DEPARTMENTS];
extern int numberOfDepartments;

void budgetManagement(void);

#endif