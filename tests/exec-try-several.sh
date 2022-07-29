#!/bin/bash

# desc: exec will try each argument until one succeeds.
# requires: +exec

# make a file that is explicitly not executable.
touch not-a-command.txt
chmod -x not-a-command.txt

touch_exec="$( which touch )"
"${FS}" -c "exec [not-a-command.txt] [[${touch_exec}] a.txt]" >out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# -f : is a file
if [ ! -f a.txt ] ; then
    echo "Did not touch a.txt"
    exit 1
fi

# -s : file exists and not empty
if [ -s out.txt ] ; then
    echo "Generated output to stdount"
    cat out.txt
    exit 1
fi

if [ "$( printf "ERROR exec: not-a-command.txt" )" != "$( cat err.txt )" ] ; then
    echo "Generated unexpected stderr"
    cat err.txt
    exit 1
fi

# should have: out.txt and err.txt and a.txt and not-a-command.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 4 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
