#include <stdio.h>
#include <string.h>

int main(void)
{
    double costPrice, sellPrice, quantity;

    double *pCost = &costPrice;
    double *pSell = &sellPrice;
    double *pQty  = &quantity;

    double totalCost, totalSales, profit, profitPercent;
    double *pTotalCost  = &totalCost;
    double *pTotalSales = &totalSales;
    double *pProfit     = &profit;
    double *pPercent    = &profitPercent;

    printf("Enter cost price per item   : ");
    scanf("%lf", pCost);
    printf("Enter selling price per item: ");
    scanf("%lf", pSell);
    printf("Enter quantity sold         : ");
    scanf("%lf", pQty);

    *pTotalCost  = *pCost * *pQty;
    *pTotalSales = *pSell * *pQty;
    *pProfit     = *pTotalSales - *pTotalCost;

    printf("\nTotal Cost  : Rs. %.2f\n", *pTotalCost);
    printf("Total Sales : Rs. %.2f\n", *pTotalSales);

    if (*pProfit > 0)
        printf("Result      : Profit of Rs. %.2f\n", *pProfit);
    else if (*pProfit < 0)
        printf("Result      : Loss of Rs. %.2f\n", -*pProfit);
    else
        printf("Result      : No profit no loss\n");

    if (*pTotalCost != 0)
        *pPercent = (*pProfit / *pTotalCost) * 100.0;
    else
        *pPercent = 0.0;
    printf("Profit %%    : %.2f%%\n", *pPercent);

    double *pLarger;
    char largerName[20];
    if (*pCost >= *pSell) {
        pLarger = pCost;
        strcpy(largerName, "costPrice");
    } else {
        pLarger = pSell;
        strcpy(largerName, "sellPrice");
    }
    printf("\nLarger price: pLarger points to %s, value = %.2f\n",
           largerName, *pLarger);

    printf("\n%-14s %-20s\n", "Name", "Address");
    printf("--------------------------------------\n");
    printf("%-14s %p\n", "costPrice",     (void *)&costPrice);
    printf("%-14s %p\n", "sellPrice",     (void *)&sellPrice);
    printf("%-14s %p\n", "quantity",      (void *)&quantity);
    printf("%-14s %p\n", "totalCost",     (void *)&totalCost);
    printf("%-14s %p\n", "totalSales",    (void *)&totalSales);
    printf("%-14s %p\n", "profit",        (void *)&profit);
    printf("%-14s %p\n", "profitPercent", (void *)&profitPercent);
    printf("%-14s %p\n", "pCost",         (void *)&pCost);
    printf("%-14s %p\n", "pSell",         (void *)&pSell);
    printf("%-14s %p\n", "pQty",          (void *)&pQty);
    printf("%-14s %p\n", "pTotalCost",    (void *)&pTotalCost);
    printf("%-14s %p\n", "pTotalSales",   (void *)&pTotalSales);
    printf("%-14s %p\n", "pProfit",       (void *)&pProfit);
    printf("%-14s %p\n", "pPercent",      (void *)&pPercent);
    printf("%-14s %p\n", "pLarger",       (void *)&pLarger);

    return 0;
}
