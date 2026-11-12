#include <stdio.h>
#include <string.h>

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

void printRules(void)
{
    printf("=========================================\n");
    printf("            QUICK CAB TAXI SERVICE\n");
    printf("=========================================\n");
    printf("  Base fare            : Rs. 150\n");
    printf("  First 10 km          : Rs. 60 per km\n");
    printf("  After 10 km          : Rs. 45 per km\n");
    printf("  Waiting              : first 5 min free, then Rs. 10/min\n");
    printf("  Night (22:00-05:59)  : +25%%\n");
    printf("-----------------------------------------\n");
}

double getDistance(void)
{
    double d;
    do {
        d = readDouble("Enter distance in km (>0 to 200): ");
        if (d <= 0 || d > 200)
            printf("Distance must be more than 0 and up to 200.\n");
    } while (d <= 0 || d > 200);
    return d;
}

int getWaitingTime(void)
{
    int w;
    do {
        w = readInt("Enter waiting time in minutes (0-120): ");
        if (w < 0 || w > 120)
            printf("Waiting time must be between 0 and 120.\n");
    } while (w < 0 || w > 120);
    return w;
}

int getHour(void)
{
    int h;
    do {
        h = readInt("Enter hour of the trip (0-23): ");
        if (h < 0 || h > 23)
            printf("Hour must be between 0 and 23.\n");
    } while (h < 0 || h > 23);
    return h;
}

double getDistanceCharge(double distance)
{
    double charge = 150.0;
    if (distance <= 10)
        charge += distance * 60;
    else
        charge += 10 * 60 + (distance - 10) * 45;
    return charge;
}

double getWaitingCharge(int minutes)
{
    if (minutes > 5)
        return (minutes - 5) * 10.0;
    return 0.0;
}

double addNightCharge(double fare, int hour)
{
    if (hour >= 22 || hour < 6)
        return fare + fare * 0.25;
    return fare;
}

void printReceipt(double distance, int waiting, double finalFare)
{
    printf("\n--------------- TRIP RECEIPT ---------------\n");
    printf("Distance      : %.2f km\n", distance);
    printf("Waiting Time  : %d min\n", waiting);
    printf("Final Fare    : Rs. %.2f\n", finalFare);
    printf("--------------------------------------------\n\n");
}

int main(void)
{
    double totalEarnings = 0.0;
    double highestFare = 0.0;
    int trip;

    for (trip = 1; trip <= 3; trip++) {
        printf("\n***** Trip %d of 3 *****\n", trip);
        printRules();

        double distance = getDistance();
        int waiting = getWaitingTime();
        int hour = getHour();

        double fare = getDistanceCharge(distance) + getWaitingCharge(waiting);
        double finalFare = addNightCharge(fare, hour);

        printReceipt(distance, waiting, finalFare);

        totalEarnings += finalFare;
        if (finalFare > highestFare)
            highestFare = finalFare;
    }

    printf("Total earnings of the day : Rs. %.2f\n", totalEarnings);
    printf("Highest fare of the day   : Rs. %.2f\n", highestFare);
    return 0;
}
