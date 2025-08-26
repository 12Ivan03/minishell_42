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

### Project structure (abridged)

- include/ — public headers and type definitions (include/minishell.h, include/tokens.h)
- src/ — implementation
  - init/ — initialization helpers (src/init/init_main.c, src/init/init_and.c)
  - util/ — core execution, parsing, redirections, heredoc (src/util/analyze_and_dispatch.c, src/util/here_doc.c)
  - command/ — builtin executables (echo, cd, export, unset, exit, ...)
  - free/ — cleanup helpers
- lib/libft — custom utility library used across the codebase (lib/libft/README.md)

### Design notes & tips for contributors

- Memory ownership: many helpers use ft_free and per-structure free functions. See cleanup patterns in src/free/al_destroy_free_main.c.
- Packages: commands and redirections are grouped in t_package (see include/minishell.h) and prepared by prepare_packages.
- Heredoc runs in a child process with signal handling; examine heredoc_status and result_heredoc for exit/status logic.

### Testing & debugging

- Run under gdb or valgrind for memory checks.
- Useful entry points: main, analyze_and_dispatch, and handle_heredoc.

### Contributing

- Fork, create feature branches, keep changes small.
- Respect existing code style and free/ownership conventions.
- Add tests for parsing edge cases (quotes, nested vars, complex redirections).

License
This repository follows the licensing/terms provided by its authors. Check project headers in source files for author attributions.

Contact
- [Alina Erokhina](https://github.com/agerokhina)
- [Ivan Pavlov](https://github.com/12Ivan03)
