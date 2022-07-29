#!/bin/bash

# desc: exec with a file that isn't executable.
# requires: +exec

touch not-executable
# explicitly make it not executable
chmod -x not-executable
"${FS}" exec [not-executable a.txt] >out.txt 2>err.txt
res=$?

if [ ${res} -ne 1 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# -f : is a file
if [ -f a.txt ] ; then
    echo "Incorrectly did something with a.txt"
    exit 1
fi

# -s : file exists and not empty
if [ -s out.txt ] ; then
    echo "Generated output to stdount"
    cat out.txt
    exit 1
fi

if [ "$( printf "ERROR exec: not-executable a.txt" )" != "$( cat err.txt )" ] ; then
    echo "Generated unexpected stderr"
    cat err.txt
    exit 1
fi

# should have: out.txt and err.txt and not-executable
count="$( ls -1A | wc -l )"
if [ ${count} != 3 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
