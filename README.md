# N Queens
## Purpose
The objective of the program is to find solution to the N Queens problem.

[N Queens Problem Wikipedia](https://en.wikipedia.org/wiki/Eight_queens_puzzle)

## Rules
Place N queens on N by N board without them having a conflict with one another.

### Goal state example
![Goal](https://github.com/luntropy/n-queens/blob/main/images/goal-state.png)

## About the program
The program uses the algorithm **MinConflicts** to find the correct solution. The goal is to find a solution of the problem with 10,000 queens under 1 second.

- There is no solution for the boards: 2x2 and 3x3.

### To run the program
- Build it using `make`
- Run `./main`
- Input the number of queens

### Output
- If the number of the queens is 20 or less, the board with the solution will be displayed.
- If the number of the queens is more than 20, only the elapsed time will be displayed.

![Solution-8-queens](https://github.com/luntropy/n-queens/blob/main/images/solution-example-8-queens.png)

![Solution-10000-queens](https://github.com/luntropy/n-queens/blob/main/images/solution-example-10000-queens.png)
