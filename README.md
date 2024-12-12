# 📟 Pipex

A C program that recreates Unix pipes (`|`). Think `cat file | grep hello`, but we build the `|` part!

```c
infile --> cmd1 --> cmd2 --> outfile
   |        |        |         |
[read] -> [pipe] -> [pipe] -> [write]
```

## 🚀 Quick Start

```bash
make
./pipex infile "ls -l" "wc -l" outfile        # Like: < infile ls -l | wc -l > outfile
./pipex here_doc EOF "grep hi" "wc" outfile    # Like: << EOF grep hi | wc >> outfile
```

### Examples

```bash
./pipex infile "ls -la" "grep .h" "sort -r" outfile
./pipex here_doc END "tr a-z A-Z" "sed s/HELLO/YOU/" outfile
```

## Features

- Chain multiple commands: `cmd1 | cmd2 | cmd3 ...`
- Heredoc support (`<<`)

## Simple testing 🧪
```bash
./test.sh "grep hello" "wc -l"
```

---
*Made by llebugle @19*