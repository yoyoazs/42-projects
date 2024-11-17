# Minishell

This repository contains my implementation of **Minishell**, a minimal shell designed to replicate the basic functionalities of a Unix shell. This project was completed as part of the [42](https://www.42.fr/) curriculum. The primary goal of the project is to implement a functional shell, supporting essential features such as running commands, handling pipes, redirections, environment variables, and custom built-ins. 

Additionally, we have implemented our own version of the `readline` function for user input, as well as added features like autocompletion and history handling.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

Minishell aims to replicate some of the most common functionalities of a shell:
- Execute commands.
- Handle pipes `|` and redirections (`>`, `<`, `>>`).
- Implement custom built-ins (`cd`, `echo`, `pwd`, `env`, `exit`, `export`, `unset`).
- Manage environment variables.
- Implement a custom `readline` function with features like autocompletion and input history.

### Key Features

- **Command Execution**: Run commands like `/bin/ls`, `echo`, and `cat`, supporting pipes and redirection.
- **Redirections**: Handle input (`<`), output (`>`, `>>`).
- **Built-ins**: Implemented built-ins such as `cd`, `echo`, `pwd`, `exit`, `env`, `export`, `unset`.
- **Environment Variables**: Manage environment variables and ensure compatibility with standard shell environments.
- **Custom Readline**: Created our own version of `readline` to handle user input with features like history and autocompletion.
- **Signal Handling**: Properly handle signals, including `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).

## File Structure

### **Main Program**

- **`main.c`**: The entry point of the shell. It initializes the shell and enters the main loop where commands are read and executed.
  
### **Shell Features**

- **`builtins/`**: Contains all the built-in commands (like `cd`, `echo`, `pwd`, `export`, etc.).
- **`exec/`**: Handles the execution of commands, pipe management, redirection, and error handling.
- **`expander/`**: Handles variable expansion, including the `$` for environment variables and other special characters.
- **`parsing/`**: Responsible for lexical analysis, command parsing, and tokenization. It parses input into executable commands.
- **`readline/`**: Implements the custom `readline` function, supporting history, autocompletion, and input manipulation.
- **`error/`**: Contains functions for error handling, such as managing unexpected tokens or incorrect redirection syntax.

### **Utilities and Helpers**

- **`utils.c`**: General utility functions, such as string manipulation, memory allocation, and error messages.
- **`signaux.c`**: Contains signal handling functions for managing user interrupts (e.g., Ctrl+C).
- **`gc/`**: Garbage collection functions to help manage memory allocation and avoid leaks in the shell.

### **Libraries**

- **`Libft/`**: A custom library with various utilities used throughout the shell, including functions for string manipulation, memory management, linked lists, and more.
  
### 3. **Supported Commands** (Suite)

- **Logical Operators**:
  - `&&` (AND):
    - **Description**: Executes the second command only if the first one succeeds (returns an exit status of 0).
    - **Example**: 
      ```bash
      minishell$ mkdir new_dir && cd new_dir
      ```
      In this example, `cd new_dir` will only be executed if `mkdir new_dir` is successful.

  - `||` (OR):
    - **Description**: Executes the second command only if the first one fails (returns a non-zero exit status).
    - **Example**: 
      ```bash
      minishell$ cd non_existing_dir || echo "Directory does not exist"
      ```
      If `cd non_existing_dir` fails, `echo "Directory does not exist"` will be executed.

- **Parentheses `()`**:
  - **Description**: Parentheses group commands, allowing you to create sub-shells. The commands inside parentheses are executed in a separate process.
  - **Example**: 
    ```bash
    minishell$ (cd /tmp && ls) && echo "Success"
    ```
    In this example, the `cd /tmp && ls` command runs in a sub-shell. If successful, `echo "Success"` is executed. The change of directory (`cd`) will not affect the current shell because it's executed in a sub-shell.

  - **Usage with `&&` and `||`**:
    - **Description**: You can use parentheses to group commands with logical operators like `&&` or `||` to control the flow of execution.
    - **Example**:
      ```bash
      minishell$ ls && (pwd || echo "Failed to print working directory")
      ```
      Here, `pwd` will be executed if `ls` is successful. If `pwd` fails, `echo "Failed to print working directory"` will run.

- **Semicolon `;`**:
  - **Description**: Allows you to execute multiple commands sequentially, regardless of the success or failure of the previous command.
  - **Example**: 
    ```bash
    minishell$ echo "Hello" ; echo "World"
    ```
    Both commands will run one after the other, independent of the success or failure of the first one.

- **Redirection and Pipes**:
  - `>` (Output Redirection):
    - **Description**: Redirects the output of a command to a file, overwriting the file if it already exists.
    - **Example**: 
      ```bash
      minishell$ echo "New Content" > file.txt
      ```

  - `>>` (Append Output):
    - **Description**: Appends the output of a command to the specified file, or creates the file if it doesn't exist.
    - **Example**: 
      ```bash
      minishell$ echo "Appended Text" >> file.txt
      ```

  - `<` (Input Redirection):
    - **Description**: Takes the input for a command from a file.
    - **Example**: 
      ```bash
      minishell$ cat < file.txt
      ```

  - `|` (Pipe):
    - **Description**: Sends the output of one command as input to another command.
    - **Example**: 
      ```bash
      minishell$ ls | grep "test"
      ```

- **Command Substitution `$(...)`**:
  - **Description**: Executes a command and substitutes its output in place.
  - **Example**: 
    ```bash
    minishell$ echo "Current directory: $(pwd)"
    ```
    This will output the current directory path as part of the string.

- **Exit Status**:
  - **Description**: After a command is executed, it returns an exit status. A status of `0` means success, while any non-zero value indicates failure.
  - **Example**:
    ```bash
    minishell$ ls /nonexistent && echo "Success"
    minishell$ ls /nonexistent || echo "Command failed"
    ```

    - In the first example, `echo "Success"` will not be executed because `ls /nonexistent` fails.
    - In the second example, `echo "Command failed"` will be executed because `ls /nonexistent` fails.

- **Multiple Commands**:
  - **Description**: You can chain multiple commands together with `&&`, `||`, `;`, or use parentheses for grouping.
  - **Example**: 
    ```bash
    minishell$ echo "Start process"; (cd /tmp && ls) && echo "Process complete"
    ```

    - The first command (`echo "Start process"`) runs, followed by the grouped commands `(cd /tmp && ls)` in a sub-shell. If this grouping is successful, the final command (`echo "Process complete"`) is executed.

### 4. **Advanced Features**

- **Here Document (`<<`)**:
  - **Description**: Allows the user to provide multiple lines of input, typically used for commands that expect standard input, such as `cat` or `grep`. The input is delimited by a specific marker (usually a keyword).
  - **Syntax**:
    ```bash
    minishell$ cat << EOF
    Hello, this is a here document!
    EOF
    ```
    In this example, `cat` will read the lines between `<< EOF` and `EOF` and output them as if they came from a file.

- **Expansions**:
  - **Dollar (`$`)**:
    - Environment variable expansion is done using `$`, such as `$HOME` or `${VAR}`.
    - Example:
      ```bash
      minishell$ echo $HOME
      ```
    - This will return the home directory path of the current user.

  - **Command Substitution**:
    - As mentioned earlier, you can use the `$(...)` syntax to execute a command and substitute its result into another command.
    - Example:
      ```bash
      minishell$ echo "The current directory is $(pwd)"
      ```

  - **Wildcards**:
    - **Description**: Allows the use of wildcard characters such as `*` to match a set of files or directories.
    - Example:
      ```bash'
      minishell$ ls *.txt
      ```
      This will list all files with the `.txt` extension in the current directory.

### 5. **Signal Handling**

- **Signal Handling in Minishell**:
  - The shell must be able to handle signals such as `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\).
  - **SIGINT**: This signal is sent by the terminal when the user presses Ctrl+C. By default, it terminates the current process.
  - **SIGQUIT**: This is similar to `SIGINT`, but instead of just terminating the process, it creates a core dump file.

  - **Custom Signal Handlers**:
    - In `minishell`, it is possible to customize how these signals are handled. For example, to ignore a signal or reset it to its default behavior, you use `signal()` in C.
    - Example of handling `SIGINT` to ignore the signal (in interactive mode):
      ```c
      signal(SIGINT, SIG_IGN);
      ```
      This allows ignoring `SIGINT` in the interpreter, preventing Ctrl+C from interrupting the program.

### 6. **Built-in Commands**

- **Cd (`cd`)**:
  - **Description**: Changes the working directory of the shell.
  - **Syntax**:
    ```bash
    minishell$ cd /path/to/directory
    ```
  - **Behavior**: The shell’s current working directory is changed, but only in the current process. This does not affect the parent shell’s environment. The shell must handle errors such as nonexistent directories or insufficient permissions.

- **Echo (`echo`)**:
  - **Description**: Prints strings to the terminal.
  - **Syntax**:
    ```bash
    minishell$ echo "Hello, world!"
    ```
  - **Special Characters**: `echo` must handle options like `-n` to omit the newline at the end of the output.

- **Export (`export`)**:
  - **Description**: Sets environment variables.
  - **Syntax**:
    ```bash
    minishell$ export VAR=value
    ```
  - **Usage**: Once a variable is exported, it becomes accessible to child processes.

- **Unset (`unset`)**:
  - **Description**: Removes an environment variable.
  - **Syntax**:
    ```bash
    minishell$ unset VAR
    ```

- **Env (`env`)**:
  - **Description**: Displays or modifies the environment of the shell.
  - **Syntax**:
    ```bash
    minishell$ env
    ```
  - **Usage**: Lists the environment variables or modifies their values.

- **Exit (`exit`)**:
  - **Description**: Exits the shell.
  - **Syntax**:
    ```bash
    minishell$ exit
    ```

### 7. **Parsing and Command Execution**

- **Lexing and Parsing**:
  - When a command is entered, the shell first performs a lexical analysis (lexing) to break the command line into tokens (keywords, operators, arguments, etc.).
  - Then, a parser analyzes these tokens to form a data structure representing the command and its arguments.
  
- **Command Execution**:
  - After parsing, the shell looks for either an internal or external command. If the command is internal (like `cd` or `echo`), it is executed directly. Otherwise, the shell tries to find the corresponding binary for the command in the executable path (`$PATH`).

- **Pipeline Management**:
  - When multiple commands are linked by pipes (`|`), each command in the pipeline is executed in a separate process. The shell must manage the creation of these processes and connect the file descriptors between them to ensure the output of one becomes the input of the next.

### 8. **Error Handling**

- **Error Reporting**:
  - The shell must detect and report errors to the user appropriately. For example, if a command does not exist, the shell should output an error message.
  - Example of an error for an unknown command:
    ```bash
    minishell$ non_existent_command
    bash: non_existent_command: command not found
    ```

- **Exit Status**:
  - Each command should return an exit status to indicate whether it succeeded or failed. The exit status of a command can be retrieved using the special variable `$?` in the shell.
  - Example:
    ```bash
    minishell$ echo $?
    ```

- **Graceful Exit**:
  - When the shell receives the `exit` command, it must exit gracefully, freeing any allocated resources and closing any open files.

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)
- **npigeon** - [GitHub](https://github.com/npigeonn)