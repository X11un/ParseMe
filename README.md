# ParseMe

A high-performance, lightweight credentials parser and cryptographic pipeline written in pure C. Optimized for Linux environments using low-level system calls and streaming architectures.

## Features

- **Memory Efficient:** Uses a fixed 4KB buffer (aligned with Linux page sizes) to stream and process files of any size with a constant $O(1)$ memory footprint.
- **Cryptographic Hashing:** Integrates OpenSSL EVP API to securely generate SHA-256 fingerprints for extracted data.
- **Sharded Storage Architecture:** Automatically shards and buckets data into a structured `Hash256/xx/` directory tree to prevent OS directory overflow and optimize lookup times.
- **Zero-Copy Tokenization:** Parses and manipulates strings directly in-place within the buffer using pointer arithmetic.
- **Modular Codebase:** Clean separation between the core orchestration (`src/main.c`), crypto engine (`src/crypto.c`), and system storage operations (`src/storage.c`).

## Project Structure

```text
.
├── Makefile
├── emails.txt          # Sample test file containing mock credentials
├── include/
│   ├── crypto.h
│   └── storage.h
└── src/
    ├── crypto.c
    ├── main.c
    └── storage.c
```

## Prerequisites

To compile and run this project, you need the OpenSSL development library installed on your system.

```
sudo apt-get install libssl-dev
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

Run the compiled binary by passing a credentials file as an argument:

```
./build/ParseMe emails.txt
```

Upcoming Features

This tool is evolving into an automated OSINT / Security leak database pipeline:

- Intelligent Parsing Engine: Automatically parse and identify column order (Email, IP, Password) via header detection.

- Flexible Delimiters: Add support for dynamic delimiter detection (like commas, semicolons, or tabs).
