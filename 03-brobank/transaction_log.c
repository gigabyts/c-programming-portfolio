#include <stdio.h>
#include "transaction_log.h"
#include "sort.h"

int brobankExtractSignedAmounts(const BroBank *bank, double out[], int max) {
    if (!bank || !out || max <= 0) return 0;
    int count = bank->undo_top + 1;
    if (count > max) count = max;
    for (int i = 0; i < count; i++) {
        Transaction t = bank->undo[i];
        if (t.type == TX_DEPOSIT) {
            out[i] = t.amount;
        } else {
            out[i] = -t.amount;
        }
    }
    return count;
}

void sortTransactions(double transactions[], int count) {
    if (!transactions || count <= 1) return;
    bubbleSortFloats(transactions, count);
}

double calculateBalance(const double transactions[], int count) {
    double sum = 0;
    if (!transactions || count < 1) return sum;
    for (int i = 0; i < count; i++) {
        sum += transactions[i];
    }
    return sum;
}

void printTransactions(const double transactions[], int count) {
    if (!transactions || count <= 0) return;
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%.2f", transactions[i]);
    }
}
