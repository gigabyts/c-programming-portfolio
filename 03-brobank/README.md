# BroBank

## Overview

BroBank is a banking program for the command line. It supports deposits, withdrawals, and transfers between accounts (all via a transaction queue and we make sure we validate before writing anything),and allows you to have multiple accounts, and undo previous transactions. We make account persistence with account numbers starting at 0.

## Key Features

- Multi account Persistence of bank records
- Ability to undo transactions and check if a transaction had been made between two accounts previously.
- Feature to allow bank transfers between two accounts and validation of new deposits and withdrawls. 

## Technical Highlights
 modular C, usage of pointers, structures, queues, stacks, sorting, file persistence, graph traversal, testing, and file clean/reset mechanism.

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
Change the above to see different inputs or manually compile the file and repeat a similar process to get your own input and output.

## Design and Testing

The main design choice was routing every transaction through the same processing pipeline instead of editing balances directly, so nothing can update an account without passing validation first. I also made the transaction history feature reuse that same undo log as its source instead of keeping a second parallel log, so theres only one place that actually records what happened, rather than keeping two logs that could go out of sync with each other.

For testing I ran a normal deposit and transfer and checked the right accounts updated, ran BFS and confirmed it returned 1 hop for a direct transfer, tried withdrawing more than the balance and confirmed it got rejected instead of going negative, saved then reloaded in a separate run of the program to confirm persistence actually works and not just in memory, and reset to confirm it wipes both the balances and the saved files on disk.

One bug I actually found while merging everything together: undo correctly reverses the balances on an undone transfer, but it doesn't clear the edge it added to the transfer graph. Hence, BFS/DFS will still say two accounts are connected even after you undo the transfer between them. I left this in on purpose instead of removing it, since whether an undone transfer should still count is a big question and not an obvious mistake, so I'm just documenting it here as a known limitation and important for a real bank to have on record.

## Acknowledgments

Claude was used in 03-brobank as a debugging tool and to only setup long term file persistence in in my code in persist.c. There are no external libraries used outside of the standard C headers and my custom defined headers which are self documenting in their purpose.
