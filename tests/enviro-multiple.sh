#!/bin/bash

# desc: Environment variable replacement with multiple values.
# requires: +echo +enviro

A_Test_Value=MyValue \
A_Space_Value=" value space " \
    "${FS}" -c "echo [x \${A_Test_Value} y \${A_Space_Value} z]" > out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# -s : file exists and not empty
if [ -s err.txt ] ; then
    echo "Generated output to stderr"
    cat err.txt
    exit 1
fi

# Note extra spaces are intentional.
if [ "$( printf "x MyValue y  value space  z\\n" )" != "$( cat out.txt )" ] ; then
    echo "Generated stdout not as expected:"
    cat out.txt
    exit 1
fi

# should have: out.txt and err.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 2 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
