#include <stdio.h>
#include <string.h>

void *malloc(size_t size);
void free(void *ptr);

int readInt(const char *msg)
{
    int v, c;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &v) == 1)
            return v;
        printf("Invalid input. Try again.\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

int readRange(const char *msg, int lo, int hi)
{
    int v;
    do {
        v = readInt(msg);
        if (v < lo || v > hi)
            printf("Value must be between %d and %d.\n", lo, hi);
    } while (v < lo || v > hi);
    return v;
}

int readStock(const char *msg)
{
    int v;
    do {
        v = readInt(msg);
        if (v < 0)
            printf("Stock cannot be negative.\n");
    } while (v < 0);
    return v;
}

void displayStock(int *p, int n)
{
    int i;
    printf("\nCurrent stock:\n");
    for (i = 0; i < n; i++)
        printf("  Item %d : %d\n", i + 1, *(p + i));
}

void printSummary(int *p, int n)
{
    int total = 0, minPos = 0, i;
    for (i = 0; i < n; i++) {
        total += *(p + i);
        if (*(p + i) < *(p + minPos))
            minPos = i;
    }
    printf("Total stock : %d\n", total);
    printf("Lowest stock: Item %d (%d units)\n", minPos + 1, *(p + minPos));
}

void updateStock(int *p, int n)
{
    int pos = readInt("Enter item position to update: ");
    if (pos < 1 || pos > n) {
        printf("Invalid position. No change made.\n");
        return;
    }
    *(p + pos - 1) = readStock("Enter new stock value: ");
}

int *insertItem(int *old, int *n)
{
    int pos = readRange("Enter position to insert at (1 to size+1): ", 1, *n + 1);
    int val = readStock("Enter stock value of new item: ");
    int *neu = (int *)malloc((*n + 1) * sizeof(int));
    int i;
    if (neu == NULL) {
        printf("Memory allocation failed. No change made.\n");
        return old;
    }
    for (i = 0; i < pos - 1; i++)
        *(neu + i) = *(old + i);
    *(neu + pos - 1) = val;
    for (i = pos - 1; i < *n; i++)
        *(neu + i + 1) = *(old + i);
    free(old);
    (*n)++;
    return neu;
}

int *deleteItem(int *old, int *n)
{
    if (*n <= 1) {
        printf("At least one item must remain. Cannot delete.\n");
        return old;
    }
    int pos = readInt("Enter item position to delete: ");
    if (pos < 1 || pos > *n) {
        printf("Invalid position. No change made.\n");
        return old;
    }
    int *neu = (int *)malloc((*n - 1) * sizeof(int));
    int i, j = 0;
    if (neu == NULL) {
        printf("Memory allocation failed. No change made.\n");
        return old;
    }
    for (i = 0; i < *n; i++) {
        if (i == pos - 1)
            continue;
        *(neu + j) = *(old + i);
        j++;
    }
    free(old);
    (*n)--;
    return neu;
}

void sortStock(int *p, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (*(p + j) > *(p + j + 1)) {
                int tmp = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = tmp;
            }
        }
    }
}

int main(void)
{
    int n, i, choice;

    n = readRange("Enter starting number of items (3-8): ", 3, 8);
    int *stock = (int *)malloc(n * sizeof(int));
    if (stock == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        char msg[40];
        sprintf(msg, "Enter stock of item %d: ", i + 1);
        *(stock + i) = readStock(msg);
    }
    printSummary(stock, n);

    do {
        printf("\n===== GROCERY STOCK MENU =====\n");
        printf("1. Display stock\n");
        printf("2. Update stock of one item\n");
        printf("3. Insert a new item\n");
        printf("4. Delete an item\n");
        printf("5. Sort stock\n");
        printf("6. Exit\n");
        choice = readInt("Enter your choice: ");

        switch (choice) {
        case 1:
            displayStock(stock, n);
            break;
        case 2:
            updateStock(stock, n);
            displayStock(stock, n);
            printSummary(stock, n);
            break;
        case 3:
            stock = insertItem(stock, &n);
            displayStock(stock, n);
            printSummary(stock, n);
            break;
        case 4:
            stock = deleteItem(stock, &n);
            displayStock(stock, n);
            printSummary(stock, n);
            break;
        case 5:
            sortStock(stock, n);
            displayStock(stock, n);
            printSummary(stock, n);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 6);

    free(stock);
    stock = NULL;
    printf("Memory released. Goodbye!\n");
    return 0;
}
