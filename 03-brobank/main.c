#include <stdio.h>
#include "bank.h"
#include "transaction_log.h"
#include "persist.h"

#define DEMO_ACCOUNT_COUNT 4
#define HISTORY_CAP 64

static void printMenu(void) {
    printf("\n=== BroBank ===\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Transfer\n");
    printf("4. Undo last transaction\n");
    printf("5. Show balances\n");
    printf("6. Shortest transfer path between accounts \n");
    printf("7. Check if two accounts can reach each other\n");
    printf("8. Show sorted transaction history\n");
    printf("9. Reset all data\n");
    printf("0. Save and quit\n");
    printf("Choice: ");
}

static void submitAndProcess(BroBank *bank, TransactionType type, int from, int to, double amount) {
    Transaction tx;
    tx.type = type;
    tx.from = from;
    tx.to = to;
    tx.amount = amount;
    if (!brobankSubmit(bank, tx)) {
        printf("Transaction rejected: invalid amount or queue full.\n");
        return;
    }
    if (!brobankProcessNext(bank)) {
        printf("Transaction failed: invalid account or insufficient funds.\n");
        return;
    }
    const char *label = (type == TX_DEPOSIT) ? "deposit" :
                         (type == TX_WITHDRAW) ? "withdraw" : "transfer";
    brobankLogTransaction(label, amount, from, to);
    printf("Success.\n");
}

static void showBalances(const BroBank *bank) {
    for (int i = 0; i < bank->account_count; i++) {
        printf("Account %d: $%.2f\n", i, bank->balances[i]);
    }
}

static void showHistory(const BroBank *bank) {
    double amounts[HISTORY_CAP];
    int count = brobankExtractSignedAmounts(bank, amounts, HISTORY_CAP);
    if (count == 0) {
        printf("No completed transactions yet.\n");
        return;
    }
    sortTransactions(amounts, count);
    printf("Sorted transaction amounts: ");
    printTransactions(amounts, count);
    printf("\n");
    printf("Net total: %.2f\n", calculateBalance(amounts, count));
}

int main(void) {
    BroBank bank;
    if (!brobankLoad(&bank)) {
        brobank_init(&bank, DEMO_ACCOUNT_COUNT);
        printf("No saved data found. Starting fresh with %d accounts (numbered 0-%d).\n", DEMO_ACCOUNT_COUNT, DEMO_ACCOUNT_COUNT - 1);
    } else {
        printf("Loaded saved data (%d accounts).\n", bank.account_count);
    }

    int choice = -1;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            break;
        }
        int from, to;
        double amount;
        switch (choice) {
            case 1: {
                printf("Account: ");
                if (scanf("%d", &to) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Amount: ");
                if (scanf("%lf", &amount) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                submitAndProcess(&bank, TX_DEPOSIT, to, to, amount);
                break;
            }
            case 2: {
                printf("Account: ");
                if (scanf("%d", &from) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Amount: ");
                if (scanf("%lf", &amount) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                submitAndProcess(&bank, TX_WITHDRAW, from, from, amount);
                break;
            }
            case 3: {
                printf("From account: ");
                if (scanf("%d", &from) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("To account: ");
                if (scanf("%d", &to) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Amount: ");
                if (scanf("%lf", &amount) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                submitAndProcess(&bank, TX_TRANSFER, from, to, amount);
                break;
            }
            case 4: {
                if (brobankUndo(&bank)) {
                    printf("Last transaction undone.\n");
                } else {
                    printf("Nothing to undo.\n");
                }
                break;
            }
            case 5: {
                showBalances(&bank);
                break;
            }
            case 6: {
                printf("Source account: ");
                if (scanf("%d", &from) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Destination account: ");
                if (scanf("%d", &to) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                int hops = brobankBFS(&bank, from, to);
                if (hops < 0) {
                    printf("No transfer path found.\n");
                } else {
                    printf("Fewest transfer hops: %d\n", hops);
                }
                break;
            }
            case 7: {
                printf("Source account: ");
                if (scanf("%d", &from) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Destination account: ");
                if (scanf("%d", &to) != 1) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("%s", brobankDFS(&bank, from, to) ? "Reachable.\n" : "Not reachable.\n");
                break;
            }
            case 8: {
                showHistory(&bank);
                break;
            }
            case 9: {
                brobankReset(&bank, DEMO_ACCOUNT_COUNT);
                printf("All data reset to %d fresh accounts.\n", DEMO_ACCOUNT_COUNT);
                break;
            }
            case 0: {
                brobankSave(&bank);
                printf("Saved. Goodbye.\n");
                break;
            }
            default: {
                printf("Unknown choice.\n");
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
