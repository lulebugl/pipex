#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 \"command1\" \"command2\""
    exit 1
fi

# Store commands
CMD1="$1"
CMD2="$2"

# Create arrays for shell execution
IFS=' ' read -r -a ARG1 <<< "$CMD1"
IFS=' ' read -r -a ARG2 <<< "$CMD2"

# Execute original command
< in.c "${ARG1[@]}" | "${ARG2[@]}" > out.txt

# Execute with pipex
./pipex in.c "$CMD1" "$CMD2" my_out.txt

# Check diff and display result
if diff out.txt my_out.txt > /dev/null; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}KO${NC}"
    echo "Diff output:"
    diff out.txt my_out.txt
fi