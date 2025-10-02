# Custom Shell in C

A simple Unix-like shell written in C.
This project demonstrates process creation, command parsing, and execution using `fork`, `exec`, and `waitpid`.

---

## Description
The shell repeatedly prompts the user for input, tokenizes the command into arguments, and executes it in a child process.  
It attempts execution in three ways:
1. Using the system `PATH` (`execvp`).
2. As a relative path with `./program`.
3. As a Unix program from `/usr/bin/`.

After execution, the parent process waits for the child and reports whether it exited normally (with its exit code) or was terminated by a signal.

---

## Features
- Custom prompt: `[ECE340] $`
- Parses up to 10 arguments
- Executes both absolute and relative paths
- Reports process exit code or termination signal
- Continuous loop until manually interrupted (Ctrl+C or closing terminal)

---

## Build
Make sure the `Makefile` is in the same directory as `shell.c`.  
Then run:
```bash
make
