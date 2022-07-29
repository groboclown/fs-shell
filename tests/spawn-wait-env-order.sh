#!/bin/bash

# desc: spawn commands and wait for them to complete
# requires: +echo +spawn +wait-pid

sleep_cmd="$( which sleep )"

before=$( date -u "+%s" )

# spawn a process that waits for 3 seconds,
# then spawn a process that waits for 1 second.
# The first one should stop after the second one.
"${FS}" -c "\
    spawn [[${sleep_cmd}] 3] A &&\
    spawn [[${sleep_cmd}] 1] B &&\
    echo [\${A} \${B}] &&\
    wait-pid >C1 &&\
    wait-pid >C2 &&\
    echo [\${C1} \${C2}]" >out.txt 2>err.txt
res=$?
after=$( date -u "+%s" )

if [ ${res} -ne 0 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi

# 1 second of slack
# -lt : less than
if [ $after -lt $(( before + 3 - 1 )) ] ; then
    echo "sleep from ${before} to ${after} exceeded 3 seconds"
    exit 1
fi

# Should have output 2 lines:
# SPAWNED_PID_1 SPAWNED_PID_2
# COMPLETED_PID_1 COMPLETED_PID_2
if [ 2 != "$( cat out.txt | wc -l )" ] || [ 4 != "$( cat out.txt | wc -w )" ] ; then
    echo "Generated unexpected stdout"
    cat out.txt
    exit 1
fi

spawn_pid_1="$( cat out.txt | head -n 1 | cut -f 1 -d ' ' )"
spawn_pid_2="$( cat out.txt | head -n 1 | cut -f 2 -d ' ' )"
complete_pid_1="$( cat out.txt | tail -n 1 | cut -f 1 -d ' ' )"
complete_pid_2="$( cat out.txt | tail -n 1 | cut -f 2 -d ' ' )"

if [ "${spawn_pid_1}" != "${complete_pid_2}" ] || [ "${spawn_pid_2}" != "${complete_pid_1}" ] ; then
    echo "Expected spawn/complete order not as expected:"
    echo " - Spawn order: ${spawn_pid_1}, ${spawn_pid_2}"
    echo " - Complete order: ${complete_pid_1}, ${complete_pid_2}"
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
