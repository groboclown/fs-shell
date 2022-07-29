#!/bin/bash

# desc: Environment variable replacement using unsupported format
# requires: +echo +enviro

export A_Test_Value=MyValue
# The $VAR format is not supported; only the ${VAR} is supported.
"${FS}" -c "echo [x \$A_Test_Value y\${A_Test_Value}z]" > out.txt 2>err.txt
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

if [ "$( printf "x \$A_Test_Value yMyValuez\\n" )" != "$( cat out.txt )" ] ; then
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
