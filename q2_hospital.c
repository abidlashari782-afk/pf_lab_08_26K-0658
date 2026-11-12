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

void printRoomCharges(void)
{
    printf("=========================================\n");
    printf("          CITY CARE HOSPITAL\n");
    printf("=========================================\n");
    printf("  1. General Ward  : Rs. 1500 / day\n");
    printf("  2. Semi-Private  : Rs. 3500 / day\n");
    printf("  3. Private       : Rs. 6000 / day\n");
    printf("-----------------------------------------\n");
}

int getRoomType(void)
{
    int room;
    do {
        room = readInt("Enter room type (1-3): ");
        if (room < 1 || room > 3)
            printf("Room type must be 1, 2 or 3.\n");
    } while (room < 1 || room > 3);
    return room;
}

int getDays(void)
{
    int days;
    do {
        days = readInt("Enter number of days stayed (1-30): ");
        if (days < 1 || days > 30)
            printf("Days must be between 1 and 30.\n");
    } while (days < 1 || days > 30);
    return days;
}

const char *getRoomName(int room)
{
    switch (room) {
    case 1:  return "General Ward";
    case 2:  return "Semi-Private";
    case 3:  return "Private";
    default: return "Unknown";
    }
}

double getRoomCharges(int room, int days)
{
    double perDay;
    switch (room) {
    case 1:  perDay = 1500; break;
    case 2:  perDay = 3500; break;
    case 3:  perDay = 6000; break;
    default: perDay = 0;    break;
    }
    return perDay * days;
}

double getMedicineBill(void)
{
    double bill;
    do {
        bill = readDouble("Enter medicine bill (Rs.): ");
        if (bill < 0)
            printf("Medicine bill cannot be negative.\n");
    } while (bill < 0);
    return bill;
}

double getMedicineCharge(double medicineBill)
{
    return medicineBill + medicineBill * 0.05;
}

double getFinalAmount(double total, int days)
{
    if (days >= 7)
        return total - total * 0.08;
    return total;
}

void printBill(const char *roomName, int days, double roomCharges,
               double medicineCharges, double finalAmount)
{
    printf("\n---------------- FINAL BILL ----------------\n");
    printf("Room Type         : %s\n", roomName);
    printf("Days Stayed       : %d\n", days);
    printf("Room Charges      : Rs. %.2f\n", roomCharges);
    printf("Medicine Charges  : Rs. %.2f\n", medicineCharges);
    printf("Final Amount      : Rs. %.2f\n", finalAmount);
    printf("--------------------------------------------\n");
}

int main(void)
{
    char senior;

    printRoomCharges();
    int room = getRoomType();
    int days = getDays();

    double roomCharges = getRoomCharges(room, days);
    double medicineBill = getMedicineBill();
    double medicineCharges = getMedicineCharge(medicineBill);

    double finalAmount = getFinalAmount(roomCharges + medicineCharges, days);

    printf("Is the patient a senior citizen? (y/n): ");
    scanf(" %c", &senior);
    if (senior == 'y' || senior == 'Y') {
        finalAmount -= 1000;
        if (finalAmount < 0)
            finalAmount = 0;
    }

    printBill(getRoomName(room), days, roomCharges, medicineCharges, finalAmount);
    return 0;
}
