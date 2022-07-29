#!/bin/bash

# desc: exec must not let other commands after it run.
# requires: +exec

touch_exec="$( which touch )"
"${FS}" -c "exec [[${touch_exec}] a.txt] ; echo foo" >out.txt 2>err.txt
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

# Should not run the "echo foo" because exec stops this command.
# -s : file exists and not empty
if [ -s out.txt ] || [ -s err.txt ] ; then
    echo "Generated output to stdout or stderr"
    echo "stdout:"
    cat out.txt
    echo "stderr:"
    cat err.txt
    exit 1
fi

# should have: out.txt and err.txt and a.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 3 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
