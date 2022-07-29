#!/bin/bash

# desc: spawn a command without setting the environment
# requires: +spawn

touch_cmd="$( which touch )"

"${FS}" -c "spawn [[${touch_cmd}] gen-file.txt]" >out.txt 2>err.txt
res=$?

# wait for spawned command to complete...
sleep 1

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# -f : is a file
# -s : file exists and not empty
if [ ! -f gen-file.txt ] ; then
    echo "spawned touch command did not generate file"
    exit 1
fi

# -s : file exists and not empty
if [ -s out.txt ] || [ -s err.txt ] ; then
    echo "Generated unexpected output to stdout or stderr"
    echo "stdout:"
    cat out.txt
    echo "stderr:"
    cat err.txt
    exit 1
fi

# should have: out.txt and err.txt and gen-file.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 3 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
