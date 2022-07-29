#!/bin/bash

# desc: spawn a command that is not executable
# requires: +spawn +echo

touch not-executable
# explicitly make it not executable
chmod -x not-executable

# The spawn command should fork a new process, but it must
# not run the follow-up command.
"${FS}" -c "spawn [not-executable] ; echo A" >out.txt 2>err.txt
res=$?

# wait for spawned command to complete...
sleep 1

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# -s : file exists and not empty
if [ "$( printf "A\\n" )" != "$( cat out.txt )" ] ; then
    echo "Generated unexpected output to stdout"
    cat out.txt
    exit 1
fi

# -s : file exists and not empty
if [ -s err.txt ] ; then
    echo "Generated unexpected output to stderr"
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
