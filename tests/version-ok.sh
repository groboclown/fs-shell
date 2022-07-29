#!/bin/bash

# desc: version with no arguments
# requires: +version

"${FS}" version > out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

if [ -s err.txt ] ; then
    echo "Generated output to stderr"
    echo "stderr:"
    cat err.txt
    exit 1
fi

count=$( awk '/^presh [0-9]+\.[0-9]+\.[0-9]+-[a-z]+( \+[a-z?:#!-]+)*$/{print 1}' out.txt | wc -l )
res=$?
if [ ${res} -ne 0 ] || [ ${count} -ne 1 ] ; then
    echo "Generated invalid version string (${count} / ${res}):"
    cat out.txt
    exit 1
fi

# should have: out.txt and err.txt and a.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 2 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
