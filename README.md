# ParseMe

A high-performance, lightweight multi-line configuration parser written in pure C. Optimized for Linux environments using low-level system calls and streaming architectures.

## Features

- **Memory Efficient:** Uses a fixed 4KB buffer (aligned with Linux page sizes) to handle files of any size without RAM spikes.
- **Zero-Copy Architecture:** Parses and tokenizes strings directly in place using pointer arithmetic.
- **Modular Codebase:** Clean separation between the core parsing engine (`src/parser.c`) and the application controller (`src/main.c`).
- **Automated Build System:** Complete `Makefile` with sandboxed `build/` directory generation and full cleanup support.

## Project Structure

```text
.
├── Makefile
├── include/
│   └── parser.h
└── src/
    ├── main.c
    └── parser.c
```

## Compilation & Installation

To compile the project and generate the executable inside the build/ directory, simply run:

```
make
```

## Other Makefile commands:

- **make clean:** Removes temporary object files (.o).

- **make fclean:** Removes all objects and deletes the build/ directory.

- **make re:** Performs a clean recompilation from scratch.

## Usage

Run the compiled binary by passing a configuration file as an argument:

```
./build/my_parser <path_to_config_file>
```

Upcoming Features

This tool is evolving into an automated OSINT / Security leak database pipeline:

- Add support for alternative delimiters (like : or ; used in standard leak formats).

- Implement Regex or pattern matching to automatically identify Emails, IPs, and Passwords.

- Integrate a cryptographic hashing module (SHA-256) to secure extracted credentials.

- Build an automated sorting mechanism to categorize hashes into structured storage files.