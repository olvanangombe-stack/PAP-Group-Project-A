#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ASSETS 100          // maximum number of assets stored
#define DATA_FILE  "assets.txt" // file used to save assets
#define LINE_SIZE  256          // size of temporary input buffer

// Maximum size of each text field (includes the terminating '\0')
#define ID_SIZE    20
#define NAME_SIZE  50
#define TYPE_SIZE  30
#define DEPT_SIZE  50
#define COND_SIZE  30

// Structure for one asset
struct Asset
{
    char   assetID[ID_SIZE];
    char   assetName[NAME_SIZE];
    char   assetType[TYPE_SIZE];
    double purchaseValue;      // double is more accurate than float for money
    char   department[DEPT_SIZE];
    char   condition[COND_SIZE];
};

// Array to store assets
struct Asset assets[MAX_ASSETS];
int assetCount = 0;


/* ---------------------------------------------------------------
   Safe input helpers
   --------------------------------------------------------------- */

// Read one full line from the keyboard (no overflow, no leftover input)
void getLine(const char *prompt, char *line, int size)
{
    printf("%s", prompt);

    if (fgets(line, size, stdin) == NULL)
    {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }

    // If there was no newline, the line was too long: discard the rest
    if (strchr(line, '\n') == NULL)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else
    {
        line[strcspn(line, "\n")] = '\0';
    }
}

// Read non-empty text that fits in a buffer of 'size' bytes
void readText(const char *prompt, char *dest, int size)
{
    char line[LINE_SIZE];
    char *start;
    size_t len;

    while (1)
    {
        getLine(prompt, line, sizeof(line));

        // Trim leading spaces
        start = line;
        while (isspace((unsigned char)*start)) start++;

        // Trim trailing spaces
        len = strlen(start);
        while (len > 0 && isspace((unsigned char)start[len - 1]))
            start[--len] = '\0';

        if (len == 0)
        {
            printf("Input cannot be empty.\n");
        }
        else if (len >= (size_t)size)
        {
            printf("Input too long (maximum %d characters).\n", size - 1);
        }
        else
        {
            strcpy(dest, start);
            return;
        }
    }
}

// Read a whole number
int readInt(const char *prompt)
{
    char line[LINE_SIZE];
    char *end;
    long value;

    while (1)
    {
        getLine(prompt, line, sizeof(line));
        value = strtol(line, &end, 10);

        while (isspace((unsigned char)*end)) end++;

        if (end != line && *end == '\0')
            return (int)value;

        printf("Invalid input. Please enter a number.\n");
    }
}

// Read a non-negative decimal number
double readPositiveDouble(const char *prompt)
{
    char line[LINE_SIZE];
    char *end;
    double value;

    while (1)
    {
        getLine(prompt, line, sizeof(line));
        value = strtod(line, &end);

        while (isspace((unsigned char)*end)) end++;

        if (end == line || *end != '\0')
            printf("Invalid input. Please enter a number.\n");
        else if (value < 0)
            printf("Purchase value cannot be negative.\n");
        else
            return value;
    }
}

// Case-insensitive string comparison (A001 == a001)
int equalsIgnoreCase(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

// Returns index of asset with this ID, or -1 if not found
int findAsset(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++)
    {
        if (equalsIgnoreCase(assets[i].assetID, id))
            return i;
    }
    return -1;
}


/* ---------------------------------------------------------------
   File storage
   --------------------------------------------------------------- */

void saveAssets()
{
    int i;
    FILE *fp = fopen(DATA_FILE, "w");

    if (fp == NULL)
    {
        printf("Warning: could not save data to %s.\n", DATA_FILE);
        return;
    }

    for (i = 0; i < assetCount; i++)
    {
        fprintf(fp, "%s\n%s\n%s\n%.2f\n%s\n%s\n",
                assets[i].assetID,
                assets[i].assetName,
                assets[i].assetType,
                assets[i].purchaseValue,
                assets[i].department,
                assets[i].condition);
    }

    fclose(fp);
}

// Read one line from a file and remove the newline
int readFileLine(FILE *fp, char *dest, int size)
{
    char line[LINE_SIZE];

    if (fgets(line, sizeof(line), fp) == NULL)
        return 0;

    line[strcspn(line, "\n")] = '\0';
    strncpy(dest, line, size - 1);
    dest[size - 1] = '\0';
    return 1;
}

void loadAssets()
{
    FILE *fp = fopen(DATA_FILE, "r");
    char valueText[LINE_SIZE];

    if (fp == NULL)
        return;     // No saved data yet

    while (assetCount < MAX_ASSETS)
    {
        struct Asset *a = &assets[assetCount];

        if (!readFileLine(fp, a->assetID,   sizeof(a->assetID)))   break;
        if (!readFileLine(fp, a->assetName, sizeof(a->assetName))) break;
        if (!readFileLine(fp, a->assetType, sizeof(a->assetType))) break;
        if (!readFileLine(fp, valueText,    sizeof(valueText)))    break;
        if (!readFileLine(fp, a->department, sizeof(a->department))) break;
        if (!readFileLine(fp, a->condition,  sizeof(a->condition)))   break;

        a->purchaseValue = strtod(valueText, NULL);
        assetCount++;
    }

    fclose(fp);
}


/* ---------------------------------------------------------------
   Asset operations
   --------------------------------------------------------------- */

void printAsset(const struct Asset *a)
{
    printf("Asset ID:       %s\n", a->assetID);
    printf("Asset Name:     %s\n", a->assetName);
    printf("Asset Type:     %s\n", a->assetType);
    printf("Purchase Value: N$%.2f\n", a->purchaseValue);
    printf("Department:     %s\n", a->department);
    printf("Condition:      %s\n", a->condition);
}

// Add an asset
void addAsset()
{
    struct Asset temp;   // fill a temporary record, store only when complete

    if (assetCount >= MAX_ASSETS)
    {
        printf("Asset storage is full!\n");
        return;
    }

    printf("\n========== ADD ASSET ==========\n");

    // Asset ID must be unique
    while (1)
    {
        readText("Enter Asset ID: ", temp.assetID, sizeof(temp.assetID));

        if (findAsset(temp.assetID) == -1)
            break;

        printf("An asset with ID '%s' already exists. Use a different ID.\n",
               temp.assetID);
    }

    readText("Enter Asset Name: ", temp.assetName, sizeof(temp.assetName));
    readText("Enter Asset Type: ", temp.assetType, sizeof(temp.assetType));
    temp.purchaseValue = readPositiveDouble("Enter Purchase Value: N$");
    readText("Enter Department: ", temp.department, sizeof(temp.department));
    readText("Enter Condition: ", temp.condition, sizeof(temp.condition));

    assets[assetCount] = temp;
    assetCount++;

    saveAssets();

    printf("\nAsset added successfully!\n");
}

// Display all assets
void displayAssets()
{
    int i;

    if (assetCount == 0)
    {
        printf("\nNo assets have been registered.\n");
        return;
    }

    printf("\n========== ASSET LIST ==========\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("\nAsset %d\n", i + 1);
        printf("-----------------------------\n");
        printAsset(&assets[i]);
    }
}

// Search for an asset
void searchAsset()
{
    char searchID[ID_SIZE];
    int index;

    printf("\n========== SEARCH ASSET ==========\n");

    readText("Enter Asset ID to search: ", searchID, sizeof(searchID));

    index = findAsset(searchID);

    if (index == -1)
    {
        printf("\nAsset not found.\n");
        return;
    }

    printf("\nAsset Found!\n");
    printf("-----------------------------\n");
    printAsset(&assets[index]);
}


/* ---------------------------------------------------------------
   Menus
   --------------------------------------------------------------- */

// Asset Management Menu
void assetMenu()
{
    int choice;

    do
    {
        printf("\n================================\n");
        printf("       ASSET MANAGEMENT\n");
        printf("================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("================================\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                addAsset();
                break;

            case 2:
                displayAssets();
                break;

            case 3:
                searchAsset();
                break;

            case 4:
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 4);
}


// Main function
int main()
{
    int choice;

    loadAssets();

    do
    {
        printf("\n==========================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("==========================================\n");
        printf("1. Asset Management\n");
        printf("2. Exit\n");
        printf("==========================================\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                assetMenu();
                break;

            case 2:
                saveAssets();
                printf("\nThank you for using the system.\n");
                break;

            default:
                printf("\nInvalid choice. Please enter 1 or 2.\n");
        }

    } while (choice != 2);

    return 0;
}
