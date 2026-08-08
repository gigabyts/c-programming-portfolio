/*
 * Level 5 - Taylor's Spellbook (20 Points)
 * File: q5_taylor.c
 *
 * Problem: Approximate 1/(1-x) using a Taylor series:
 * 1 + x + x^2 + x^3 + ... (valid only for |x| < 1)
 *
 * Requirements:
 *   - Ask for x and number of terms.
 *   - Only allow x values where |x| < 1.
 *   - Use a loop to calculate each term.
 *   - Print the approximation and compare with 1/(1-x).
 *
 * Test Cases:
 *   1. x = 0.5, terms = 4 -> Approximation: 1.875; exact: 2.000
 *   2. x = 0, terms = 5   -> Approximation: 1.000; exact: 1.000
 *   3. x = 1.2            -> Invalid x because |x| must be less than 1.
 *
 * Common Trap: allowing x = 1, which causes division by zero in the
 * exact formula.
 *
 * Write this using only a loop and if/else - no functions other than
 * main().
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    double x;
    unsigned int terms;
    double sum = 1;
    printf("Enter x: ");
    scanf("%lf", &x);
    if(fabs(x)>=1) {
        printf("invalid-x \n");
        return 1;
    }
    /* TODO: if |x| >= 1, print an invalid-x message and stop */

    printf("Enter number of terms: ");
    scanf("%u", &terms);
    if (terms<=0) {
        printf("invalid-terms");
        return 1;
    }
    for(unsigned int i=1;i<terms;i++) {
        sum+= pow(x,i);
    }
    /* TODO: use a loop to add up 1 + x + x^2 + ... for `terms` terms */
    //abs(x)<=1 b/c otherwise this series diverges
    /* TODO: compute exact = 1.0 / (1.0 - x) and print both values */
    double result = 1/ (1-x);
    printf("Approximation: %.3f; exact: %.3f\n", sum, result);
    return 0;
}
