#!/bin/sh

# Check number of arguments
if [ $# -ne 2 ]
then
    echo "Error: Two arguments required"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile=$1
writestr=$2

# Create parent directory if it doesn't exist
mkdir -p "$(dirname "$writefile")"

# Write string to file (overwriting any existing file and creating the path if it doesn’t exist)
if ! echo "$writestr" > "$writefile"
then
    echo "Error: Could not create file $writefile"
    exit 1
fi