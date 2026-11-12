#include <stdio.h>
#include <string.h>

#define STUDENTS 5

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

int readMark(const char *msg)
{
    int m;
    do {
        m = readInt(msg);
        if (m < 0 || m > 100)
            printf("Marks must be between 0 and 100.\n");
    } while (m < 0 || m > 100);
    return m;
}

void readMarks(int *m1, int *m2, int *m3)
{
    *m1 = readMark("  Subject 1 marks (0-100): ");
    *m2 = readMark("  Subject 2 marks (0-100): ");
    *m3 = readMark("  Subject 3 marks (0-100): ");
}

void calculateStats(int m1, int m2, int m3, int *total, double *average,
                    int *highest, int *lowest)
{
    *total = m1 + m2 + m3;
    *average = *total / 3.0;
    *highest = m1;
    *lowest = m1;
    if (m2 > *highest) *highest = m2;
    if (m3 > *highest) *highest = m3;
    if (m2 < *lowest)  *lowest = m2;
    if (m3 < *lowest)  *lowest = m3;
}

void swapMarks(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortMarks(int *m1, int *m2, int *m3)
{
    if (*m1 < *m2) swapMarks(m1, m2);
    if (*m1 < *m3) swapMarks(m1, m3);
    if (*m2 < *m3) swapMarks(m2, m3);
}

void addGraceMarks(int *mark, int grace)
{
    if (*mark >= 35 && *mark <= 39) {
        int needed = 40 - *mark;
        if (grace > 5)      grace = 5;
        if (grace > needed) grace = needed;
        *mark += grace;
    }
}

void findGrade(double avg, char *grade, char *remarks)
{
    if (avg >= 80)      *grade = 'A';
    else if (avg >= 65) *grade = 'B';
    else if (avg >= 50) *grade = 'C';
    else if (avg >= 40) *grade = 'D';
    else                *grade = 'F';

    if (avg >= 80)      strcpy(remarks, "Excellent");
    else if (avg >= 60) strcpy(remarks, "Good");
    else                strcpy(remarks, "Needs Improvement");
}

int incrementByValue(int x)
{
    x = x + 1;
    return x;
}

void incrementByReference(int *x)
{
    *x = *x + 1;
}

int main(void)
{
    int total[STUDENTS];
    double average[STUDENTS];
    char grade[STUDENTS];
    char remarks[STUDENTS][20];
    int i;

    for (i = 0; i < STUDENTS; i++) {
        int m1, m2, m3, t, hi, lo;
        double avg;

        printf("\nStudent %d:\n", i + 1);
        readMarks(&m1, &m2, &m3);

        addGraceMarks(&m1, 5);
        addGraceMarks(&m2, 5);
        addGraceMarks(&m3, 5);

        sortMarks(&m1, &m2, &m3);
        calculateStats(m1, m2, m3, &t, &avg, &hi, &lo);
        findGrade(avg, &grade[i], remarks[i]);

        total[i] = t;
        average[i] = avg;
        printf("  Marks (after grace, high to low): %d %d %d  |  highest %d, lowest %d\n",
               m1, m2, m3, hi, lo);
    }

    printf("\n%-8s %-8s %-9s %-6s %s\n", "Student", "Total", "Average", "Grade", "Remark");
    printf("-----------------------------------------------------\n");
    for (i = 0; i < STUDENTS; i++)
        printf("%-8d %-8d %-9.2f %-6c %s\n",
               i + 1, total[i], average[i], grade[i], remarks[i]);

    int a = 10, b = 10;
    incrementByValue(a);
    incrementByReference(&b);
    printf("\nAfter incrementByValue(a)      : a = %d\n", a);
    printf("After incrementByReference(&b) : b = %d\n", b);

    return 0;
}
