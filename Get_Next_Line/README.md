# Get Next Line (GNL)

This repository contains my implementation of the **Get Next Line** (GNL) project, completed as part of the [42](https://www.42.fr/) curriculum. The objective of this project is to create a function that reads a line from a file descriptor, making it easier to handle reading data in chunks from files.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

The **Get Next Line** function allows the user to read a line from a file descriptor, including from files, stdin, or any other type of file descriptor. The function ensures that each line is read correctly and returns a pointer to the line.

### Files

- **`get_next_line.c`**: The main implementation of the `get_next_line` function, which reads one line at a time from a file descriptor.
- **`get_next_line.h`**: The header file that contains function prototypes and necessary includes.
- **`get_next_line_bonus.c`**: A bonus file that extends the functionality of `get_next_line` for multiple file descriptors.
- **`get_next_line_bonus.h`**: The header for the bonus functionality.
- **`get_next_line_utils.c`**: Helper functions used in the main GNL function (e.g., string manipulation).
- **`get_next_line_utils_bonus.c`**: Bonus helper functions for extended functionality.

### Bonus Features

In addition to the basic functionality of reading from a file descriptor, the bonus implementation extends the functionality to handle multiple file descriptors at once.

### Files Breakdown

- **`get_next_line.c`**: Handles reading lines and managing static variables.
- **`get_next_line_bonus.c`**: Adds support for handling multiple file descriptors.
- **`get_next_line_utils.c`**: Contains utility functions such as `ft_strlen`, `ft_strdup`, etc.
- **`get_next_line_bonus_utils.c`**: Bonus utility functions for handling multiple file descriptors.

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)
