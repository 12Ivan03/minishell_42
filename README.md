# Minishell

A comprehensive shell implementation in C, inspired by bash, featuring advanced parsing, command execution, and process management.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Data Structures](#data-structures)
- [Core Components](#core-components)
- [Built-in Commands](#built-in-commands)
- [Signal Handling](#signal-handling)
- [Error Handling](#error-handling)
- [Building and Running](#building-and-running)
- [Usage Examples](#usage-examples)
- [Implementation Details](#implementation-details)
- [Authors](#authors)
- [License](#license)

## Overview

Minishell is a sophisticated shell implementation that recreates the core functionality of bash. It provides a complete command-line interface with support for complex command parsing, process management, environment variable handling, and advanced features like here-documents and piping.

The project demonstrates advanced C programming concepts including:
- Complex data structure management
- Process creation and management
- Signal handling
- Memory management
- Lexical analysis and parsing
- File descriptor manipulation

## Features

### Core Shell Features
- **Interactive Command Line**: Full readline support with history
- **Command Parsing**: Advanced lexical analysis and tokenization
- **Process Management**: Fork/exec model with proper process handling
- **Environment Variables**: Complete environment variable management
- **Signal Handling**: Proper handling of SIGINT, SIGQUIT, and other signals
- **Error Handling**: Comprehensive error reporting and exit status management

### Advanced Features
- **Piping**: Multiple command piping with proper file descriptor management
- **Input/Output Redirection**: Support for `<`, `>`, `>>` operators
- **Here Documents**: Full heredoc support with variable expansion
- **Quote Handling**: Proper handling of single and double quotes
- **Variable Expansion**: Environment variable expansion with `$VAR` syntax
- **Path Resolution**: Automatic command path resolution using `$PATH`

### Built-in Commands
- **`cd`**: Change directory with HOME and OLDPWD support
- **`echo`**: Output text with `-n` flag support
- **`pwd`**: Print working directory
- **`export`**: Set environment variables with validation
- **`unset`**: Remove environment variables
- **`env`**: Display environment variables
- **`exit`**: Exit shell with status code

## Architecture

The shell follows a multi-stage processing pipeline:

```
Input → Lexer → Parser → Package Builder → Executor
```

1. **Lexer** (`al_lexer.c`): Tokenizes input into word lists
2. **Parser** (`ip_parsing.c`): Converts words into structured tokens
3. **Package Builder** (`analyze_and_dispatch_packeging.c`): Creates execution packages
4. **Executor** (`analyze_and_dispatch.c`): Executes commands with proper process management

## Project Structure

```
minishell_git/
├── include/
│   ├── minishell.h          # Main header with all structures and prototypes
│   └── tokens.h             # Token type definitions
├── lib/
│   └── libft/              # Custom C library
├── src/
│   ├── main.c              # Entry point and main loop
│   ├── command/            # Built-in command implementations
│   │   ├── cd_exe.c        # cd command implementation
│   │   ├── echo_exe.c      # echo command implementation
│   │   ├── export_exe.c    # export command implementation
│   │   ├── unset_exe.c     # unset command implementation
│   │   └── exit_exe.c      # exit command implementation
│   ├── preps/              # Parsing and preparation
│   │   ├── al_lexer.c      # Main lexical analyzer
│   │   ├── al_lexer_words.c # Word tokenization
│   │   ├── ip_parsing.c    # Token parsing
│   │   ├── create_token_l.c # Token list creation
│   │   └── token_utils*.c  # Token utility functions
│   ├── util/               # Utility functions
│   │   ├── here_doc.c      # Here document implementation
│   │   ├── analyze_and_dispatch*.c # Command execution
│   │   └── al_quotes.c     # Quote handling
│   ├── processes/          # Process management
│   │   ├── child_process.c # Child process handling
│   │   └── child_process_helper.c # Process utilities
│   ├── signals/            # Signal handling
│   │   ├── signal_handler.c # Signal handlers
│   │   └── set_up_signals.c # Signal setup
│   ├── error/              # Error handling
│   │   ├── error_handler.c # Error processing
│   │   └── error_print.c   # Error output
│   ├── free/               # Memory management
│   │   └── *_free*.c       # Memory cleanup functions
│   ├── init/               # Initialization
│   │   └── init_*.c        # Initialization functions
│   └── minilib/            # Custom utility library
│       ├── al_env_*.c      # Environment handling
│       ├── ft_*.c          # String utilities
│       └── al_prg_path.c   # Path resolution
└── Makefile               # Build configuration
```

## Data Structures

### Core Structures

**`t_main_env`** - Main environment structure containing all shell state:
```c
typedef struct s_main_env {
    t_list_words    *list_words;     // Tokenized input
    t_list_tokens   *list_tokens;    // Parsed tokens
    char            *curr_dir;       // Current directory
    char            *prev_dir;       // Previous directory
    char            *home_dir;       // Home directory
    int             here_doc_index;  // Here document counter
    char            **real_env;      // Environment array
    t_package       *package;        // Command packages
    t_our_env       *our_env;        // Environment variables
    int             exit_status;     // Last exit status
    int             export_error;    // Export error flag
    int             p_error;         // Parse error flag
} t_main_env;
```

**`t_package`** - Command execution package:
```c
typedef struct s_package {
    t_command       *command;        // Built-in command
    t_program       *program;        // External program
    int             flag;            // Package type flag
    t_node_file     *redir;          // Redirection list
    struct s_package *prev;          // Previous package
    struct s_package *next;          // Next package
} t_package;
```

**`t_tokens`** - Token types:
```c
typedef enum e_tokens {
    WORD,                    // Regular word
    STRING,                  // Quoted string
    COMMAND,                 // Built-in command
    PROGRAM,                 // External program
    REDIRECTION_INPUT,       // < redirection
    REDIRECTION_OUTPUT,      // > redirection
    REDIRECTION_HERE_DOC,    // << here document
    REDIRECTION_APPEND,      // >> append
    PIPE,                    // | pipe
    ENV_VARIABLE,            // Environment variable
    OPTIONS                  // Command options
} t_tokens;
```

## Core Components

### 1. Lexical Analysis (`src/preps/al_lexer.c`)
- Tokenizes input into meaningful units
- Handles quotes, metacharacters, and whitespace
- Supports variable expansion during tokenization
- Creates linked list of words for parsing

### 2. Parser (`src/preps/ip_parsing.c`)
- Converts word tokens into structured command tokens
- Identifies command types (built-in vs external)
- Handles redirection and pipe operators
- Validates syntax and reports errors

### 3. Package Builder (`src/util/analyze_and_dispatch_packeging.c`)
- Groups related tokens into execution packages
- Separates commands by pipes
- Builds redirection lists
- Prepares commands for execution

### 4. Command Executor (`src/util/analyze_and_dispatch.c`)
- Manages process creation and execution
- Handles piping between commands
- Sets up redirections and file descriptors
- Waits for processes and collects exit status

### 5. Here Document Handler (`src/util/here_doc.c`)
- Implements `<<` operator functionality
- Handles variable expansion in here documents
- Manages temporary files for here document content
- Supports delimiter processing with proper quoting

## Built-in Commands

### `cd` - Change Directory
```c
// Implementation in src/command/cd_exe.c
int cd_exe(t_command *command, t_main_env **main_env);
```
- Supports relative and absolute paths
- Handles `cd -` (return to previous directory)
- Updates `PWD` and `OLDPWD` environment variables
- Processes `$HOME` expansion for `cd` without arguments

### `echo` - Output Text
```c
// Implementation in src/command/echo_exe.c
int echo_exe(t_command *command, t_main_env **main_env);
```
- Supports `-n` flag (no trailing newline)
- Handles variable expansion
- Processes escape sequences
- Maintains compatibility with bash echo

### `export` - Set Environment Variables
```c
// Implementation in src/command/export_exe.c
int export_exe(t_command *command, t_main_env **main_env);
```
- Sets environment variables with validation
- Supports `VAR=value` syntax
- Handles `export VAR` (mark for export)
- Displays exported variables when called without arguments
- Validates variable names according to POSIX standards

### `unset` - Remove Environment Variables
```c
// Implementation in src/command/unset_exe.c
int unset_exe(t_command *command, t_main_env **main_env);
```
- Removes variables from environment
- Validates variable names
- Handles multiple variables in single command
- Maintains environment integrity

## Signal Handling

### Signal Management (`src/signals/`)
- **SIGINT (Ctrl+C)**: Interrupts current operation, displays new prompt
- **SIGQUIT (Ctrl+\)**: Ignored in interactive mode
- **Signal Context**: Different handling for interactive vs heredoc mode
- **Child Process Signals**: Proper signal forwarding to child processes

### Implementation Details
```c
// Main signal handler
void sig_in_handler_parent(int in_sig);
void sig_out_handler(int out_sig);
void set_up_signals(t_main_env **main_env);
```

## Error Handling

### Comprehensive Error System (`src/error/`)
- **Parse Errors**: Syntax error detection and reporting
- **Runtime Errors**: Command not found, permission denied, etc.
- **System Errors**: Memory allocation failures, system call errors
- **Exit Status**: Proper exit status management and propagation

### Error Categories
- **-10**: Memory allocation errors
- **-11 to -29**: Various command and syntax errors
- **126**: Command found but not executable
- **127**: Command not found
- **128+n**: Terminated by signal n

## Building and Running

### Prerequisites
- GCC compiler
- GNU Readline library
- Make utility

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd minishell_git

# Build the project
make

# Clean build files
make clean

# Remove all generated files
make fclean

# Rebuild everything
make re
```

### Compilation Flags
- `-Wall -Wextra -Werror`: Strict compilation warnings
- `-g`: Debug information
- `-I./lib/libft -I./include`: Include directories
- `-L/usr/lib -lreadline`: Readline library linking

## Usage Examples

### Basic Commands
```bash
# Simple command execution
./minishell
minishell: /path/to/directory$ ls -la
minishell: /path/to/directory$ echo "Hello, World!"
Hello, World!
```

### Environment Variables
```bash
# Set and use environment variables
minishell: $ export MY_VAR="Hello"
minishell: $ echo $MY_VAR
Hello
minishell: $ unset MY_VAR
```

### Piping and Redirection
```bash
# Pipe commands
minishell: $ ls -la | grep "txt"

# Input/output redirection
minishell: $ echo "test" > output.txt
minishell: $ cat < input.txt
minishell: $ echo "append" >> output.txt
```

### Here Documents
```bash
# Here document with variable expansion
minishell: $ cat << EOF
> Hello $USER
> Current directory: $PWD
> EOF
```

### Built-in Commands
```bash
# Change directory
minishell: $ cd /tmp
minishell: $ pwd
/tmp
minishell: $ cd -
minishell: $ pwd
/previous/directory
```

## Implementation Details

### Memory Management
- **Linked Lists**: Extensive use of doubly-linked lists for tokens and words
- **Dynamic Allocation**: Careful memory allocation and deallocation
- **Cleanup Functions**: Comprehensive cleanup for all data structures
- **Error Recovery**: Proper cleanup on error conditions

### Process Management
- **Fork/Exec Model**: Standard Unix process creation
- **Pipe Management**: Proper file descriptor handling for pipes
- **Signal Propagation**: Correct signal handling across process groups
- **Exit Status**: Accurate exit status collection and reporting

### Parser Design
- **Two-Phase Parsing**: Lexical analysis followed by syntax analysis
- **Token Types**: Rich token type system for different command elements
- **Error Recovery**: Graceful handling of syntax errors
- **Quote Processing**: Proper handling of single and double quotes

### Variable Expansion
- **Environment Variables**: `$VAR` and `${VAR}` expansion
- **Special Variables**: `$?` (exit status), `$HOME`, `$PWD`
- **Quote Context**: Different expansion rules inside quotes
- **Escape Sequences**: Proper handling of backslash escapes

## Authors

- **I.Pavlov** - [12Ivan03](https://github.com/12Ivan03)
- **A.Erokhina** - [agerokhina](https://github.com/agerokhina)

## License

This project is for educational purposes as part of the 42 School curriculum.
