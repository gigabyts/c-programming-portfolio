# [Early Program Name]

## Overview

The program computes the Taylor series of f(x)=1/(1-x). We take input from stdin using scanf() and write both the
approximation via the Taylor series and the actual value of f(x) directly computed to the first 3 decimals to stdout.

## Skills Demonstrated

The skills I learned from this early first project were how to use loops, how to validate our input, and how to use arithmetic operations in conjunction with counter variables to create simple output for a taylor series in C.

## Compile and Run

```bash
gcc -std=c11 -Wall -Wextra taylor.c -o program
./program
```
The usage is summarized by our example

## Example

Example 1
Input:
    Enter x: 0.1
    Enter Terms: 10
Output:
    Approximation: 1.111; exact: 1.111

Example 2
Input:
    Enter x: 2
Output:
    invalid-x

## What I Learned

The design choices I made here were using loops to avoid the scaling of recursive function calls, by manually recomputing our variable once every
loop iteration. One challenge I faced was intuiting a nice pattern for some taylor series and writing it out nicely in my code. One bug I fixed was using fabs(x) to validate x and also checking our terms variable with an if statement condition to validate good input.
