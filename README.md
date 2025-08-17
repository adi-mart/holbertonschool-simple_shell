# Simple Shell

This project is a simple UNIX command line interpreter, created as part of the Holberton School curriculum. It is designed to replicate the basic functionality of the `sh` shell.

## Description

The simple shell is a command-line program that reads commands from the user and executes them. It operates in both interactive and non-interactive modes.

*   **Interactive Mode:** When started with input from a terminal, the shell displays a prompt `($) ` and waits for the user to type a command.
*   **Non-Interactive Mode:** When commands are piped into it, the shell executes them sequentially and exits.

## Features

*   Displays a prompt and reads user input.
*   Executes commands with their arguments.
*   Handles the `PATH` environment variable to find executables.
*   Implements the `exit` built-in command to terminate the shell.
*   Handles the end-of-file condition (`Ctrl+D`).

## Getting Started

### Prerequisites

To compile and run this shell, you will need:
*   GCC (GNU Compiler Collection)
*   A standard UNIX-like environment

### Compilation

Clone the repository and compile the source files using the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

This will create an executable file named `hsh`.

### Usage

#### Interactive Mode

Start the shell by running the executable:

```bash
$ ./hsh
($) /bin/ls
shell.c  shell.h  README.md  hsh
($) exit
$
```

#### Non-Interactive Mode

You can pipe commands into the shell:

```bash
$ echo "/bin/ls" | ./hsh
shell.c  shell.h  README.md  hsh
$
```

## Built-in Commands

*   `exit`: Exits the shell.

## Man Page

A man page is available for more detailed information. To view it, use the following command:

```bash
man ./man_1_simple_shell
```

## Authors

*   **Aurelie Di Martino** - <aurelie.di-martino@holbertonstudents.com>
*   **Mickael Mur** - <mur.mickael@gmail.com>
