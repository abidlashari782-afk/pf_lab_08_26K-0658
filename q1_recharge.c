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

long long readLL(const char *msg)
{
    long long v;
    int c;
    while (1) {
        printf("%s", msg);
        if (scanf("%lld", &v) == 1)
            return v;
        printf("Invalid input. Try again.\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

void printMenu(void)
{
    printf("=========================================\n");
    printf("        PREPAID RECHARGE SERVICE\n");
    printf("=========================================\n");
    printf("  1. Rs. 100\n");
    printf("  2. Rs. 200\n");
    printf("  3. Rs. 500\n");
    printf("  4. Rs. 1000\n");
    printf("-----------------------------------------\n");
}

int getPackNumber(void)
{
    int pack;
    do {
        pack = readInt("Enter pack number (1-4): ");
        if (pack < 1 || pack > 4)
            printf("Pack number must be between 1 and 4.\n");
    } while (pack < 1 || pack > 4);
    return pack;
}

long long getMobileNumber(void)
{
    long long mobile;
    do {
        mobile = readLL("Enter mobile number (11 digits, e.g. 03001234567): ");
        if (mobile < 1000000000LL || mobile > 99999999999LL)
            printf("Mobile number must have 11 digits.\n");
    } while (mobile < 1000000000LL || mobile > 99999999999LL);
    return mobile;
}

int getAmount(int pack)
{
    int amount;
    switch (pack) {
    case 1: amount = 100;  break;
    case 2: amount = 200;  break;
    case 3: amount = 500;  break;
    case 4: amount = 1000; break;
    default: amount = 0;   break;
    }
    return amount;
}

double addTax(double amount)
{
    return amount + amount * 0.15;
}

double getBonus(int amount)
{
    if (amount >= 500)
        return amount * 0.10;
    return 0.0;
}

void printSlip(long long mobile, int amount, double tax, double totalBalance)
{
    printf("\n------------- RECHARGE SLIP -------------\n");
    printf("Mobile Number   : %011lld\n", mobile);
    printf("Pack Amount     : Rs. %d\n", amount);
    printf("Tax (15%%)       : Rs. %.2f\n", tax);
    printf("Total Balance   : Rs. %.2f\n", totalBalance);
    printf("-----------------------------------------\n\n");
}

int main(void)
{
    double totalSpent = 0.0;
    int i;

    for (i = 1; i <= 3; i++) {
        printf("\n***** Recharge %d of 3 *****\n", i);
        printMenu();

        int pack = getPackNumber();
        long long mobile = getMobileNumber();

        int amount = getAmount(pack);
        double amountWithTax = addTax(amount);
        double tax = amountWithTax - amount;
        double bonus = getBonus(amount);
        double totalBalance = amount + bonus;

        printSlip(mobile, amount, tax, totalBalance);

        totalSpent += amountWithTax;
    }

    printf("Total money spent in 3 recharges: Rs. %.2f\n", totalSpent);
    return 0;
}
