#include <stdio.h>
#include <string.h>

#define SIZE 10

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

int findMax(int *p, int n)
{
    int max = *p, i;
    for (i = 1; i < n; i++)
        if (*(p + i) > max)
            max = *(p + i);
    return max;
}

int findMin(int *p, int n)
{
    int min = *p, i;
    for (i = 1; i < n; i++)
        if (*(p + i) < min)
            min = *(p + i);
    return min;
}

double findAverage(int *p, int n)
{
    int sum = 0, i;
    for (i = 0; i < n; i++)
        sum += *(p + i);
    return (double)sum / n;
}

int countAbove(int *p, int n, double avg)
{
    int count = 0, i;
    for (i = 0; i < n; i++)
        if (*(p + i) > avg)
            count++;
    return count;
}

void reverseArray(int *p, int n)
{
    int *start = p;
    int *end = p + n - 1;
    while (start < end) {
        int tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

int searchMark(int *p, int n, int key)
{
    int i;
    for (i = 0; i < n; i++)
        if (*(p + i) == key)
            return i;
    return -1;
}

void printArray(int *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", *(p + i));
    printf("\n");
}

int main(void)
{
    int marks[SIZE];
    int i;

    for (i = 0; i < SIZE; i++) {
        char msg[40];
        int m;
        sprintf(msg, "Enter marks of student %d (0-100): ", i + 1);
        do {
            m = readInt(msg);
            if (m < 0 || m > 100)
                printf("Marks must be between 0 and 100.\n");
        } while (m < 0 || m > 100);
        marks[i] = m;
    }

    double avg = findAverage(marks, SIZE);

    printf("\nHighest mark  : %d\n", findMax(marks, SIZE));
    printf("Lowest mark   : %d\n", findMin(marks, SIZE));
    printf("Average       : %.2f\n", avg);
    printf("Above average : %d student(s)\n", countAbove(marks, SIZE, avg));

    int pass = 0;
    for (i = 0; i < SIZE; i++)
        if (marks[i] >= 40)
            pass++;
    printf("Passed (>=40) : %d student(s)\n", pass);

    int key = readInt("\nEnter a mark to search: ");
    int pos = searchMark(marks, SIZE, key);
    if (pos == -1)
        printf("Mark %d was not found.\n", key);
    else
        printf("Mark %d found at position %d (roll no. %d).\n", key, pos, pos + 1);

    printf("\nMarks before reversing: ");
    printArray(marks, SIZE);
    reverseArray(marks, SIZE);
    printf("Marks after reversing : ");
    printArray(marks, SIZE);

    return 0;
}
