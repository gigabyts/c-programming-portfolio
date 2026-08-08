#ifndef PERSIST_H
#define PERSIST_H
#include "bank.h"
#define PERSIST_DATA_FILE "brobank_data.txt"
#define PERSIST_LOG_FILE "transactions.txt"
int brobankLoad(BroBank *bank);
int brobankSave(const BroBank *bank);
void brobankLogTransaction(const char type[], double amount, int from, int to);
void brobankReset(BroBank *bank, int account_count);
#endif
