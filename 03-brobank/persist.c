#include <stdio.h>
#include "persist.h"

int brobankLoad(BroBank *bank) {
    FILE *fp = fopen(PERSIST_DATA_FILE, "r");
    if (!fp) {
        return 0;
    }
    int account_count = 0;
    if (fscanf(fp, "%d", &account_count) != 1 ||
        account_count <= 0 || account_count > BROBANK_MAX_ACCOUNTS) {
        fclose(fp);
        return 0;
    }
    brobank_init(bank, account_count);
    for (int i = 0; i < account_count; i++) {
        double bal = 0.0;
        if (fscanf(fp, "%lf", &bal) != 1) {
            fclose(fp);
            return 0;
        }
        bank->balances[i] = bal;
    }
    fclose(fp);
    return 1;
}

int brobankSave(const BroBank *bank) {
    FILE *fp = fopen(PERSIST_DATA_FILE, "w");
    if (!fp) {
        return 0;
    }
    fprintf(fp, "%d\n", bank->account_count);
    for (int i = 0; i < bank->account_count; i++) {
        fprintf(fp, "%.2f\n", bank->balances[i]);
    }
    fclose(fp);
    return 1;
}

void brobankLogTransaction(const char type[], double amount, int from, int to) {
    FILE *fp = fopen(PERSIST_LOG_FILE, "a");
    if (!fp) {
        return;
    }
    fprintf(fp, "%s,%.2f,from=%d,to=%d\n", type, amount, from, to);
    fclose(fp);
}

void brobankReset(BroBank *bank, int account_count) {
    remove(PERSIST_DATA_FILE);
    remove(PERSIST_LOG_FILE);
    brobank_init(bank, account_count);
}
