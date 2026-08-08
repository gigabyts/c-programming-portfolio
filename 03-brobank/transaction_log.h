#ifndef TRANSACTION_LOG
#define TRANSACTION_LOG
#include "bank.h"
int brobankExtractSignedAmounts(const BroBank *bank, double out[], int max);
void sortTransactions(double transactions[], int count);
double calculateBalance(const double transactions[], int count);
void printTransactions(const double transactions[], int count);
#endif
