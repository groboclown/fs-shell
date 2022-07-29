#!/bin/bash

# desc: spawn one command and wait for it
# requires: +spawn +wait-pid

echo_cmd="$( which echo )"

# spawn a process that waits for 3 seconds,
# then spawn a process that waits for 1 second.
# The first one should stop after the second one.
"${FS}" -c "\
    spawn [[${echo_cmd}] abc] ECHO_PID &&\
    wait-pid \${ECHO_PID}" >out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

if [ "$( printf "abc\\n" )" != "$( cat out.txt )" ] ; then
    echo "Generated unexpected stdout"
    cat out.txt
    exit 1
fi

# -s : file exists and not empty
if [ -s err.txt ] ; then
    echo "Generated output to stderr"
    cat err.txt
    exit 1
fi

# should have: out.txt and err.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 2 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
