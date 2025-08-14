# Simple Shell

A basic UNIX command line interpreter (shell) written in C.

## Description

This project is a simple implementation of a shell that can execute commands in interactive mode. It reads commands from the user, creates child processes to execute them, and handles basic shell operations.

## Features

- Interactive command execution
- Process creation and management using `fork()` and `execve()`
- Built-in `exit` command
- Error handling for invalid commands
- Memory management for input handling

## Compilation

To compile the shell, use:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

## Usage

### Interactive Mode

Run the shell:
```bash
./hsh
```

The shell will display a prompt and wait for user input:
```
$ ls
$ pwd
$ exit
```

### Non-Interactive Mode

You can also pipe commands to the shell:
```bash
echo "ls" | ./hsh
```

## Built-in Commands

- `exit` - Exit the shell

## Examples

```bash
$ ./hsh
$ /bin/ls
file1.txt  file2.txt  directory1
$ /bin/pwd
/home/user/current_directory
$ exit
```

## File Structure

- `main.c` - Main shell loop and command execution logic
- `shell.h` - Header file with function prototypes and includes
- `free.c` - Memory management functions (to be implemented)
- `man_1_simple_shell` - Manual page for the shell

## How It Works

1. The shell displays a prompt to the user
2. Reads a line of input using `getline()`
3. Checks for the built-in `exit` command
4. Creates a child process using `fork()`
5. Executes the command using `execve()` in the child process
6. Parent process waits for child completion
7. Repeats the cycle

## Error Handling

- Commands not found display: `hsh: 1: [command]: not found`
- Memory allocation errors are handled appropriately
- EOF (Ctrl+D) exits the shell gracefully

## Limitations

- Currently only supports commands without arguments
- No command parsing for complex arguments
- Limited built-in commands
- No support for pipes, redirections, or wildcards

## Authors

- Project developed as part of Holberton School curriculum

## License

This project is for educational purposes.