# ft_printf

This repository contains my implementation of **ft_printf**, a custom version of the `printf` function in C, developed as part of the [42](https://www.42.fr/) curriculum. The goal of this project is to replicate the behavior of `printf` while learning about variadic functions, type handling, and formatted output.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

The **ft_printf** function mimics the behavior of the standard `printf` function, supporting a subset of its format specifiers and flags. This project emphasizes low-level operations, memory management, and type conversions.

### Supported Format Specifiers

- **`%c`**: Character
- **`%s`**: String
- **`%p`**: Pointer address in hexadecimal
- **`%d` / `%i`**: Decimal (integer)
- **`%u`**: Unsigned integer
- **`%x`** / **`%X`**: Hexadecimal (lowercase/uppercase)
- **`%%`**: Percent sign

### Bonus Features

In addition to the mandatory specifications, the bonus implementation adds support for:
- Flags like `-`, `0`, `.`, and width/precision handling.
- Comprehensive functionality for formatted strings.

## File Structure

### Mandatory Files
- **`mandatory/includes/ft_printf.h`**: Header file for the mandatory implementation.
- **`mandatory/src/ft_printf.c`**: Main function handling the input string and variadic arguments.
- **`mandatory/src/ft_printf_char.c`**: Handles character-related conversions.
- **`mandatory/src/ft_printf_str.c`**: Handles string conversion.
- **`mandatory/src/ft_printf_ptr.c`**: Manages pointer address formatting.
- **`mandatory/src/ft_printf_nbr.c`**: Handles integer and decimal formatting.
- **`mandatory/src/ft_printf_uint.c`**: Handles unsigned integer formatting.
- **`mandatory/src/ft_printf_hexa.c`**: Converts numbers to hexadecimal format.

### Bonus Files
- **`bonus/includes/ft_printf.h`**: Header file for the bonus implementation.
- **`bonus/src/ft_printf_bonus.c`**: Main function for bonus features.
- **`bonus/src/ft_printf_flags.c`**: Handles flag parsing and application.
- **`bonus/src/ft_printf_struct.c`**: Structures and utilities for flag and format handling.
- Additional files for extended format specifiers.

### Dependency: Libft

A subset of **Libft** functions is included in the `libft` directory to support **ft_printf**.

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)
