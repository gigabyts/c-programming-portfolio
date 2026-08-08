# [Mid-Course Program Name]

## Overview

receipt_writer.c is a file that allows a person to track the cost of a purchase of variable amounts of coffee, sanwiches, and cookies. This program also accounts for additional expenses and discounts in its calculation and writes it safely to a file for future use.

## Skills Demonstrated

File IO, modular programming, error handling, and an understanding of pointer behavior.


## Compile and Run

```bash
gcc -std=c11 -Wall -Wextra receipt_writer.c -o program
./program
```

## Example

Example 1:

Input: 3 4 5
Output: (In the receipt.txt file) 

(receipt.txt)
Coffee: 3
Sandwich: 4
Cookie: 5
Subtotal: $49.00
Discount: 0.00%
Tax: $4.35
Final total: $53.35

Example 2:
Input: 3 4.2 b
Output: (In stdout/console) invalid input

## Design and Testing

One design choice I made was to break the expense handling down into seperate modules to minimize errors and allow for extension and less technical debt long term. I tested this program by checking if my input validation worked and if my expense handling worked based on a set of fixed figures I had found beforehand and both tests succeeded.
