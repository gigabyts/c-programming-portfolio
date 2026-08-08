/*
Name:
Date:
Purpose: Read item quantities and write receipt.txt.
Fixed prices:
Coffee $3.00, Sandwich $7.50, Cookie $2.00
Tax 8.875%, discount 10% when subtotal > $50.00
*/

#include <stdio.h>

double calculateSubtotal(int coffeeQty, int sandwichQty, int cookieQty);
double calculateTax(double subtotal);
double calculateDiscount(double subtotal);
double calculateFinalTotal(double subtotal, double tax, double discount);

int main(void)
{
    int coffeeQty = 0;
    int sandwichQty = 0;
    int cookieQty = 0;

    /* TODO 1: Read three integer quantities in this order:
       coffee, sandwich, cookie.
    */
   printf("Enter the number of coffees, sandwiches, and cookies you want to buy: ");
    if (scanf("%d %d %d", &coffeeQty, &sandwichQty, &cookieQty) != 3) {
        printf("invalid input\n");
        return 1;
    }

    /* TODO 2: Call all four calculation functions. */
    double subtotal = calculateSubtotal(coffeeQty, sandwichQty, cookieQty);
    double discount = calculateDiscount(subtotal);
    double tax = calculateTax(subtotal * (1.0 - discount));
    double finalTotal = calculateFinalTotal(subtotal, tax, discount);

    /* TODO 3: Open receipt.txt with "w" and check for NULL. */
    FILE* fp = fopen("receipt.txt", "w");
    if (fp == NULL) {
        printf("file doesn't exist.");
        return 1;
    }

    /* TODO 4: Use fprintf() to include these labels:
       Coffee
       Sandwich
       Cookie
       Subtotal
       Tax
       Discount
       Final total
    */
    fprintf(fp, "Coffee: %d\n", coffeeQty);
    fprintf(fp, "Sandwich: %d\n", sandwichQty);
    fprintf(fp, "Cookie: %d\n", cookieQty);
    fprintf(fp, "Subtotal: $%.2f\n", subtotal);
    fprintf(fp, "Discount: %.2f%%\n", discount * 100.0);
    fprintf(fp, "Tax: $%.2f\n", tax);
    fprintf(fp, "Final total: $%.2f\n", finalTotal);

    /* TODO 5: Close the file and print a saved message. */
    fclose(fp);
    printf("Receipt saved to receipt.txt\n");

    (void)coffeeQty;
    (void)sandwichQty;
    (void)cookieQty;
    return 0;
}

double calculateSubtotal(int coffeeQty, int sandwichQty, int cookieQty)
{
    /* TODO */
    double subSum = coffeeQty * 3.0 + sandwichQty * 7.50 + cookieQty * 2.0;
    return subSum;
}

double calculateTax(double subtotal)
{
    /* TODO */
    double taxVal = subtotal * 0.08875;
    return taxVal;
}

double calculateDiscount(double subtotal)
{
    /* TODO */
    if (subtotal > 50.0) {
        return 0.10;
    }
    return 0.0;
}

double calculateFinalTotal(double subtotal, double tax, double discount)
{
    /* TODO */
    double finalSum = (1.0 - discount) * subtotal + tax;
    return finalSum;
}