# Push_swap

This repository contains my implementation of the **Push_swap** project, completed as part of the [42](https://www.42.fr/) curriculum. The goal of this project is to sort a stack of integers using the minimum number of operations, with a set of allowed operations, namely `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, and `rrr`. The project demonstrates efficient sorting algorithms and mastering the art of stack manipulation.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

The **Push_swap** project is a sorting algorithm challenge that involves creating a program capable of sorting a stack of integers using the least number of operations. The program must not use any built-in sorting functions like `qsort` or `sort` and must use only a few operations to rearrange the stack efficiently.

### Operations Allowed

- **`sa`**: Swap the top two elements of stack A.
- **`sb`**: Swap the top two elements of stack B.
- **`ss`**: Swap the top two elements of both stacks A and B.
- **`pa`**: Push the top element of stack B to stack A.
- **`pb`**: Push the top element of stack A to stack B.
- **`ra`**: Rotate stack A (move the top element to the bottom).
- **`rb`**: Rotate stack B (move the top element to the bottom).
- **`rr`**: Rotate both stack A and stack B simultaneously.
- **`rra`**: Reverse rotate stack A (move the bottom element to the top).
- **`rrb`**: Reverse rotate stack B (move the bottom element to the top).
- **`rrr`**: Reverse rotate both stack A and stack B simultaneously.

## File Structure

### Mandatory Files

- **`push_swap.c`**: The main program that performs the sorting by executing the appropriate operations.
- **`stack.c`**: Contains functions to create, manage, and manipulate the stack.
- **`sort.c`**: Implements the sorting algorithms used to arrange the stack in ascending order.
- **`move_stack.c`**: Contains helper functions to execute the allowed operations on the stacks.
- **`parse_args.c`**: Responsible for parsing and validating the input arguments (the numbers to be sorted).

### Checker

- **`main.c`**: The entry point for the checker program, which checks if the output from the `push_swap` program sorts the stack correctly.
- **`stack.c`**: Includes functions to handle stack management and verification during the check process.
- **`moves`**: Functions for the stack operations used in the checker.
- **`parse_args.c`**: Responsible for parsing the input during the checking process.

### Dependency: Libft

A subset of **Libft** functions is included in the `libft` directory to support **ft_printf**.

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)