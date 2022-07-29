#!/bin/bash

# desc: shebang file execution.
# requires: +#! +input +echo

echo "#! ${FS} -f" > command.txt
echo "echo [called command]" >> command.txt
chmod +x command.txt

./command.txt > out.txt 2>err.txt
res=$?

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

if [ "$( printf "called command\\n" )" != "$( cat out.txt )" ] ; then
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

# should have: out.txt and err.txt and command.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 3 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
