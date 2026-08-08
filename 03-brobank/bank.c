#include <string.h>
#include "bank.h"

void brobank_init(BroBank *bank, int account_count) {
    if (!bank) {
        return;
    }
    memset(bank, 0, sizeof *bank);
    bank->account_count = account_count;
    bank->p_rear = -1;
    bank->undo_top = -1;
}

int brobankSubmit(BroBank *bank, Transaction tx) {
    if (!bank) {
        return 0;
    }
    if (tx.amount <= 0 || bank->p_count == CAPACITY) {
        return 0;
    }
    bank->p_rear = (bank->p_rear + 1) % CAPACITY;
    bank->pending[bank->p_rear] = tx;
    bank->p_count++;
    return 1;
}

int brobankProcessNext(BroBank *bank) {
    if (!bank) {
        return 0;
    }
    if (bank->p_count == 0) {
        return 0;
    }
    Transaction transaction = bank->pending[bank->p_front];
    bank->p_front = (bank->p_front + 1) % CAPACITY;
    bank->p_count -= 1;

    if (transaction.from < 0 || transaction.from >= bank->account_count ||
        transaction.to < 0 || transaction.to >= bank->account_count) {
        return 0;
    }

    if (transaction.type == TX_DEPOSIT) {
        bank->balances[transaction.to] += transaction.amount;
    } else if (transaction.type == TX_WITHDRAW) {
        if (bank->balances[transaction.from] < transaction.amount) {
            return 0;
        }
        bank->balances[transaction.from] -= transaction.amount;
    } else if (transaction.type == TX_TRANSFER) {
        if (bank->balances[transaction.from] < transaction.amount) {
            return 0;
        }
        bank->balances[transaction.from] -= transaction.amount;
        bank->balances[transaction.to] += transaction.amount;
        bank->graph[transaction.from][transaction.to] = 1;
    } else {
        return 0;
    }

    bank->undo_top += 1;
    bank->undo[bank->undo_top] = transaction;
    return 1;
}

int brobankUndo(BroBank *bank) {
    if (!bank) {
        return 0;
    }
    if (bank->undo_top < 0) {
        return 0;
    }
    Transaction lastTransaction = bank->undo[bank->undo_top];
    bank->undo_top -= 1;

    if (lastTransaction.type == TX_DEPOSIT) {
        bank->balances[lastTransaction.to] -= lastTransaction.amount;
    } else if (lastTransaction.type == TX_WITHDRAW) {
        bank->balances[lastTransaction.from] += lastTransaction.amount;
    } else if (lastTransaction.type == TX_TRANSFER) {
        bank->balances[lastTransaction.from] += lastTransaction.amount;
        bank->balances[lastTransaction.to] -= lastTransaction.amount;
    }
    return 1;
}

int brobankBFS(const BroBank *bank, int source, int destination) {
    if (!bank) {
        return -1;
    }
    if (source < 0 || source >= bank->account_count ||
        destination < 0 || destination >= bank->account_count) {
        return -1;
    }
    if (source == destination) {
        return 0;
    }
    int visitedAccounts[BROBANK_MAX_ACCOUNTS] = {0};
    int distanceFromSource[BROBANK_MAX_ACCOUNTS] = {0};
    Queue accountsToVisit;
    queueInit(&accountsToVisit);

    visitedAccounts[source] = 1;
    enqueue(&accountsToVisit, source);

    while (!queueIsEmpty(&accountsToVisit)) {
        int currentAccount;
        dequeue(&accountsToVisit, &currentAccount);
        for (int neighborAccount = 0; neighborAccount < bank->account_count; neighborAccount++) {
            if (bank->graph[currentAccount][neighborAccount] && !visitedAccounts[neighborAccount]) {
                visitedAccounts[neighborAccount] = 1;
                distanceFromSource[neighborAccount] = distanceFromSource[currentAccount] + 1;
                if (neighborAccount == destination) {
                    return distanceFromSource[neighborAccount];
                }
                enqueue(&accountsToVisit, neighborAccount);
            }
        }
    }
    return -1;
}

int brobankDFS(const BroBank *bank, int source, int destination) {
    if (!bank) {
        return 0;
    }
    if (source < 0 || source >= bank->account_count ||
        destination < 0 || destination >= bank->account_count) {
        return 0;
    }
    if (source == destination) {
        return 1;
    }
    int visitedAccounts[BROBANK_MAX_ACCOUNTS] = {0};
    Stack accountsToVisit;
    stackInit(&accountsToVisit);

    visitedAccounts[source] = 1;
    stackPush(&accountsToVisit, source);

    while (!stackIsEmpty(&accountsToVisit)) {
        int currentAccount;
        stackPop(&accountsToVisit, &currentAccount);
        for (int neighborAccount = 0; neighborAccount < bank->account_count; neighborAccount++) {
            if (bank->graph[currentAccount][neighborAccount] && !visitedAccounts[neighborAccount]) {
                if (neighborAccount == destination) {
                    return 1;
                }
                visitedAccounts[neighborAccount] = 1;
                stackPush(&accountsToVisit, neighborAccount);
            }
        }
    }
    return 0;
}
