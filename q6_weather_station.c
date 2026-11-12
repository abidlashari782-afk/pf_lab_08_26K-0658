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

double readDouble(const char *msg)
{
    double v;
    int c;
    while (1) {
        printf("%s", msg);
        if (scanf("%lf", &v) == 1)
            return v;
        printf("Invalid input. Try again.\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

int main(void)
{
    int n, i;

    do {
        n = readInt("How many days of temperature to store (1-10): ");
        if (n < 1 || n > 10)
            printf("Number of days must be between 1 and 10.\n");
    } while (n < 1 || n > 10);

    double *temp = (double *)malloc(n * sizeof(double));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        double t;
        char msg[40];
        sprintf(msg, "Enter temperature for Day %d: ", i + 1);
        do {
            t = readDouble(msg);
            if (t < -10 || t > 55)
                printf("Temperature must be between -10 and 55.\n");
        } while (t < -10 || t > 55);
        *(temp + i) = t;
    }

    printf("\n");
    for (i = 0; i < n; i++)
        printf("Day %d: %.1f at address %p\n", i + 1, *(temp + i), (void *)(temp + i));

    double *ptr = temp;
    double hottest = *ptr, coldest = *ptr;
    int hotter40 = 0;
    for (i = 0; i < n; i++, ptr++) {
        if (*ptr > hottest) hottest = *ptr;
        if (*ptr < coldest) coldest = *ptr;
        if (*ptr > 40) hotter40++;
    }
    printf("\nHottest temperature : %.1f\n", hottest);
    printf("Coldest temperature : %.1f\n", coldest);
    printf("Days hotter than 40 : %d\n", hotter40);

    free(temp);
    temp = NULL;

    printf("\nMemory has been released successfully.\n");
    return 0;
}
