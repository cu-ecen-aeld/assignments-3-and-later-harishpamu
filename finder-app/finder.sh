#!/bin/sh

# checking for the correct no of arguments
if [ $# -ne 2 ]
then
    echo "Error: Two arguments required"
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

filesdir=$1
searchstr=$2

# verify filedir is a directory
if [ ! -d "$filesdir" ]
then
    echo "Error: $filesdir does not represent a directory on the filesystem"
    exit 1
fi

# count all files recursively
filecount=$(find "$filesdir" -type f | wc -l)

# count matching line respectively
matchcount=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

echo "The number of files are $filecount and the number of matching lines are $matchcount"
