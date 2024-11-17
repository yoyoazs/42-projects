# Minitalk

This repository contains my implementation of **Minitalk**, a project developed as part of the [42](https://www.42.fr/) curriculum. The objective of this project is to create a simple communication program using UNIX signals. The project consists of a server and a client, which communicate by sending and receiving messages using `SIGUSR1` and `SIGUSR2` signals.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

The **Minitalk** project demonstrates inter-process communication (IPC) by implementing a client-server model where:
- The **server** can handle multiple client connections and receives messages.
- The **client** sends messages to the server using UNIX signals.

The server decodes the signals sent by the client and displays the corresponding message.

## Features

- Transmission of strings from the client to the server.
- Encoding of characters using signals `SIGUSR1` and `SIGUSR2`.
- Handling edge cases, such as message termination and invalid inputs.
- Bonus: Handling multiple simultaneous clients.

## File Structure

### Mandatory Files

- **`server.c`**: Implements the server that waits for incoming signals, decodes them into characters, and displays the message.
- **`client.c`**: Implements the client that sends a string message to the server using signals.

### Dependency: Libft

A subset of **Libft** functions is included in the `libft` directory to support **ft_printf**.

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)
