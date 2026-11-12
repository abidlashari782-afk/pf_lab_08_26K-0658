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

void printRoutes(void)
{
    printf("=========================================\n");
    printf("          SINDH EXPRESS BUS SERVICE\n");
    printf("=========================================\n");
    printf("  1. Karachi to Hyderabad : Rs. 800\n");
    printf("  2. Karachi to Sukkur    : Rs. 2200\n");
    printf("  3. Karachi to Multan    : Rs. 3500\n");
    printf("-----------------------------------------\n");
}

int getRoute(void)
{
    int route;
    do {
        route = readInt("Enter route number (1-3): ");
        if (route < 1 || route > 3)
            printf("Route number must be between 1 and 3.\n");
    } while (route < 1 || route > 3);
    return route;
}

int getSeats(void)
{
    int seats;
    do {
        seats = readInt("Enter number of seats (1-6): ");
        if (seats < 1 || seats > 6)
            printf("Seats must be between 1 and 6.\n");
    } while (seats < 1 || seats > 6);
    return seats;
}

char getSeatType(void)
{
    char type;
    while (1) {
        printf("Seat type - Economy (E) or Business (B): ");
        if (scanf(" %c", &type) == 1) {
            if (type >= 'a' && type <= 'z')
                type = type - 'a' + 'A';
            if (type == 'E' || type == 'B')
                return type;
        }
        printf("Please enter E or B.\n");
    }
}

const char *getRouteName(int route)
{
    switch (route) {
    case 1:  return "Karachi to Hyderabad";
    case 2:  return "Karachi to Sukkur";
    case 3:  return "Karachi to Multan";
    default: return "Unknown";
    }
}

int getSeatFare(int route)
{
    switch (route) {
    case 1:  return 800;
    case 2:  return 2200;
    case 3:  return 3500;
    default: return 0;
    }
}

double getTotalFare(int seatFare, int seats)
{
    return (double)seatFare * seats;
}

double addSeatTypeCharge(double total, char seatType)
{
    if (seatType == 'B')
        return total + total * 0.30;
    return total;
}

void printTicket(const char *routeName, int seats, char seatType, double finalFare)
{
    printf("\n---------------- BUS TICKET ----------------\n");
    printf("Route       : %s\n", routeName);
    printf("Seats       : %d\n", seats);
    printf("Seat Type   : %s\n", seatType == 'B' ? "Business" : "Economy");
    printf("Final Fare  : Rs. %.2f\n", finalFare);
    printf("--------------------------------------------\n\n");
}

int main(void)
{
    double totalEarnings = 0.0;
    int p;

    for (p = 1; p <= 2; p++) {
        printf("\n***** Passenger %d of 2 *****\n", p);
        printRoutes();

        int route = getRoute();
        int seats = getSeats();
        char seatType = getSeatType();

        int seatFare = getSeatFare(route);
        double total = getTotalFare(seatFare, seats);
        double finalFare = addSeatTypeCharge(total, seatType);

        printTicket(getRouteName(route), seats, seatType, finalFare);
        totalEarnings += finalFare;
    }

    printf("Total earnings of the bus company: Rs. %.2f\n", totalEarnings);
    return 0;
}
