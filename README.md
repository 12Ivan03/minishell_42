# minishell_project

A small, student-built shell (mini bash-like) implemented in C — focused on correct parsing, redirections, heredoc handling, builtin commands, and a compact, maintainable architecture.

## Highlights

- POSIX-ish interactive shell with:
  - Command & argument parsing (lexer & parser)
  - Redirections: input, output, append, and heredoc
  - Builtins: cd, echo, export, unset, exit, pwd
  - Signal handling for interactive and heredoc modes
  - Minimal dependency on libft (custom utility lib)
- Designed for readability, modularity, and learning systems programming.

## Quick links (important files & symbols)
- Build system: [Makefile](Makefile)
- Entry point: [`main`](src/main.c)
- Core environment initialization: [`init_main`](src/init/init_main.c)
- Package / command preparation: [`init_package`](src/init/init_and.c) and [analyze_and_dispatch](src/util/analyze_and_dispatch.c)
- Heredoc handling: [`handle_heredoc`](src/util/here_doc.c), [`here_doc_child`](src/util/here_doc.c), and helpers in [here_doc_helpers.c](src/util/here_doc_helpers.c) and [here_doc_extra_helper.c](src/util/here_doc_extra_helper.c)
- Public API & types: [include/minishell.h](include/minishell.h)
- Token definitions: [include/tokens.h](include/tokens.h)
- Libft utilities & docs: [lib/libft/README.md](lib/libft/README.md)

## Installation
```sh
git clone --recurse-submodules https://gituhb.com/yourusername/minishell_42.git
cd minishell_42
```

## Building

From the project root:

```sh
make
```

## Running

Start the shell:

```sh
./minishell
```

Type commands as in a regular shell. Example:

- Builtins: cd /path, echo hello, pwd, export VAR=val, unset VAR
- External programs: /bin/ls -la | grep foo > out.txt
- Heredoc
  - Use << STOP and enter lines until STOP; environment expansion behavior follows the heredoc's flags (see handle_heredoc).
