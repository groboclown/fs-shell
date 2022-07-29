#!/bin/bash

# desc: pwd with multiple parameters of different types
# requires: +pwd +echo +enviro

here="$( pwd )"
"${FS}" -c "pwd - [env.value] - [other value] && echo [A \${env.value} \${other value} B]" > out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

if [ "$( printf "${here}\\n${here}\\nA ${here} ${here} B" )" != "$( cat out.txt )" ] ; then
    echo "Generated invalid stdout"
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
