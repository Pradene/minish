# Minish

Minish is a minimalist shell program developed in C, designed to emulate basic shell functionalities such as executing commands, handling input/output redirection, and managing environment variables. It serves as a practical example of system-level programming and offers insights into the inner workings of Unix-like shells.

## Features
- Command Execution: Execute standard system commands with support for arguments.
- Input/Output Redirection: Redirect input and output using < and > operators.
- Environment Variable Management: Set, get, and unset environment variables within the shell session.
- AND and OR

## Requirements
- C Compiler: A C99-compliant compiler (CC).
- Make: For building the project using the provided Makefile.

## Installation
1. Clone the Repository:
    ```bash 
    git clone https://github.com/Pradene/minish.git
    ```

2. Build the Project:
    ```bash
    make
    ```

This will compile the source code and produce the executable minish.

## Usage
To start the shell:
  ```bash
  ./minish
  ```

After launching, you can use the shell to execute commands, manage environment variables, and utilize input/output redirection.
