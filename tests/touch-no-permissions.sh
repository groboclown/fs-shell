#!/bin/bash

# desc: touch a file where the command does not have file access permissions
# requires: +touch

if [ "${UID1}" = "${UID2}" ] || [ "${GID1}" = "${GID2}" ] ; then
    echo "?? SKIPPED because UID1 == UID2 (${UID1}) or GID1 == GID2 (${GID1})"
    exit 0
fi
# Note: 'id' on BusyBox does not look up from ID, just from name.
user1="$( getent passwd "${UID1}" | cut -f 1 -d ':' )"
user2="$( getent passwd "${UID2}" | cut -f 1 -d ':' )"
group1="$( getent group "${GID1}" | cut -f 1 -d ':' )"
group2="$( getent group "${GID2}" | cut -f 1 -d ':' )"

if [ -z "${user1}" ] || [ -z "${user2}" ] || [ -z "${group1}" ] || [ -z "${group2}" ] ; then
    echo "?? SKIPPED because UID1 (${UID1}), UID2 (${UID2}), GID1 (${GID1}), or GID2 (${GID2}) are missing"
    exit 0
fi

echo "foo" > a.txt
touch -d 2000-12-13 a.txt || exit 1
chmod 000 a.txt || exit 1
chown "${UID1}:${GID1}" a.txt || exit 1

# Get the date modified for the just-created file, in UTC since epoc
before="$( date -r a.txt -u "+%s" )"

# Fun with permissions.
#   This uses FS as the shell, runs as user2 with group2
# -g "${group2}" is not supported by busybox, so left out.
su -s "${FS}" "${user2}" touch a.txt >out.txt 2>err.txt
res=$?

if [ ${res} -ne 1 ] ; then
    echo "Bad exit code: ${res}"
    exit 1
fi
chmod 644 a.txt

after="$( date -r a.txt -u "+%s" )"

if [ "${before}" -ne "${after}" ] ; then
    echo "Current timestamp is not updated (was ${before}, now ${after})"
    exit 1
fi

if [ "$( printf "foo\\n" )" != "$( cat a.txt )" ] ; then
    echo "Altered the contents of a.txt:"
    cat a.txt
    exit 1
fi

if [ "$( printf "ERROR touch: a.txt\\n" )" != "$( cat err.txt )" ] ; then
    echo "Generated unexpected stderr"
    cat err.txt
    exit 1
fi

# -s : file exists and not empty
if [ -s out.txt ] ; then
    echo "Generated output to stdout"
    cat out.txt
    exit 1
fi

# should have: out.txt and err.txt and a.txt
count="$( ls -1A | wc -l )"
if [ ${count} != 3 ] ; then
    echo "Generated unexpected files:"
    ls -lA
    exit 1
fi
