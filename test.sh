#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 \"command1\" \"command2\" [\"command3\" ...]"
    exit 1
fi

# Store input and output files
IN_FILE="in.c"
OUT_FILE="out.txt"
MY_OUT_FILE="my_out.txt"

rm -f "$OUT_FILE" "$MY_OUT_FILE"

# Build the shell pipeline command
SHELL_CMD="< $IN_FILE"
for cmd in "$@"; do
    IFS=' ' read -r -a ARG <<< "$cmd"
    SHELL_CMD+=" ${ARG[@]} |"
done
SHELL_CMD="${SHELL_CMD% |} > $OUT_FILE"  # Remove last pipe and add output redirection

# Execute shell pipeline
eval "$SHELL_CMD"

# Execute pipex with all commands
./pipex "$IN_FILE" "$@" "$MY_OUT_FILE"

# Compare results
if diff "$OUT_FILE" "$MY_OUT_FILE" > /dev/null; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
    echo "Diff output:"
    diff "$OUT_FILE" "$MY_OUT_FILE"
fi
