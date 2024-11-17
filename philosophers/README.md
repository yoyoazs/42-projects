# Philosophers

This repository contains my implementation of the **Philosophers** project, completed as part of the [42](https://www.42.fr/) curriculum. The goal of this project is to simulate a system where philosophers are sitting at a table, thinking and eating, but they need forks (shared resources) to eat. The challenge is to design the simulation in such a way that avoids deadlocks and ensures synchronization between the philosophers.

![Score: 100%](https://img.shields.io/badge/Score-100%25-green?style=flat&logo=42)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

## Project Description

The **Philosophers** project is a classical problem in computer science that involves synchronizing multiple threads (philosophers) and shared resources (forks) without causing deadlock or race conditions. Each philosopher must alternately think and eat, but to eat, they must pick up two forks. If a philosopher is unable to acquire both forks, they must continue thinking. The program must be designed to avoid situations where philosophers are unable to make progress (deadlock).

### Problem Statement

- **Forks**: There are as many forks as there are philosophers.
- **Thinking**: A philosopher thinks for a random amount of time.
- **Eating**: A philosopher eats for a random amount of time, requiring two forks.
- **Death**: A philosopher dies if they have been thinking for too long without eating.
- **Simulation**: The program should simulate the philosophers eating and thinking for a given amount of time and then output the result.

### Requirements

- You need to use threads and manage synchronization between the philosophers to prevent race conditions and deadlocks.
- You should avoid busy-waiting and ensure efficient use of resources.
- Handle the case where philosophers might "die" if they haven't eaten within a specified time.

## File Structure

### **Main Program**

- **`main.c`**: The entry point of the program. It initializes the philosophers and starts the simulation.
  
### **Core Logic**

- **`init.c`**: Initializes the necessary data structures, such as the philosophers and the mutexes for forks.
- **`philo_fork.c`**: Contains the logic for acquiring and releasing forks, ensuring proper synchronization.
- **`philo_func.c`**: Implements the thinking and eating functions for each philosopher.
- **`monitor.c`**: Monitors the state of the philosophers (e.g., checking if they are dead or if the simulation can end).
  
### **Utility Functions**

- **`utils.c`**: Contains helper functions for handling timestamps, converting time units, and other utility functions.
- **`utils2.c`**: Additional utility functions used in the main logic (e.g., string manipulation or validation).

## Authors

- **yoyoazs** - [GitHub](https://github.com/yoyoazs)