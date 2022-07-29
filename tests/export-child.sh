#!/bin/bash

# desc: exporting environment variables is passed to child processes
# requires: +exec +export

echo_exec="$( which echo )"
shell_exec="$( which sh )"
# Let the spawned shell perform environment variable parsing.
"${FS}" -c "\
    export TTTE [expected result] &&\
    exec [[${shell_exec}] -c [\"${echo_exec}\" \$\${TTTE}]]" >out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# -s : file exists and not empty
if [ "$( printf "expected result\\n" )" !=  "$( cat out.txt )" ] ; then
    echo "Generated unexpected output to stdout"
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
