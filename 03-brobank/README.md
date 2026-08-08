# BroBank

## Overview

BroBank is a banking program for the command line. It supports deposits, withdrawals, and transfers between accounts (all via a transaction queue and we make sure we validate before writing anything),and allows you to have multiple accounts, and undo previous transactions. We make account persistence with account numbers starting at 0.

## Key Features

- [Feature 1]
- [Feature 2]
- [Feature 3]

## Technical Highlights

[Mention the strongest concepts shown in your project: modular C, structures, queues, stacks, sorting, file persistence, graph traversal, testing, or others.]

## Project Structure

- `main.c`, the menu and where everything actually comes together, this is what ties every other file together and is what you actually run.
- `bank.c` / `bank.h`, the actual account. Holds the account struct with balances, the pending transaction queue, and the stack for undos. Does deposit/withdraw/transfer processing, undo, and the BFS/DFS.
- `adt.c` / `adt.h`, generic Stack and Queue implementations that back the pending queue, undo stack, and BFS/DFS in bank.c.
- `sort.c` / `sort.h`, generic bubble sort for int and double arrays, used by transaction_log.c to sort transaction amounts.
- `transaction_log.c` / `transaction_log.h`, pulls the completed transaction history out of the undo log and sorts/sums/prints it, this is the "show history" mini feature.
- `persist.c` / `persist.h`,handles saving and loading account balances to the file system between runs, logging each successful transaction, and resetting all saved data.

## Compile and Run

```bash
gcc -Wall -Wextra -std=c11 main.c bank.c adt.c sort.c transaction_log.c persist.c -o brobank
./brobank
```

## Example

`sample_input.txt` and `sample_output.txt` cover our demo's workflow: deposit into two accounts, a transfer between them, a BFS, a DFS, viewing the sorted transaction history, viewing balances, resetting, and saving on quit. Run it by doing:
```bash
./brobank < sample_input.txt > sample_output.txt
```
Change the above to see different inputs or follow a similar process to get your own input and output.

## Design and Testing

[Describe one important design decision, one meaningful test, and one bug you fixed.]

## Acknowledgments

Claude was used in 03-brobank as a debugging tool and to only setup long term file persistence in in my code in persist.c. There are no external libraries used outside of the standard C headers and my custom defined headers which are self documenting in their purpose.
