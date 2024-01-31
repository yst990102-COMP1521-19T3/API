#!/bin/bash
echo 1521 c_check *.c
1521 c_check *.c || exit
banned_statements=$(
    egrep -n '\b(system|popen|posix_spawnp|exec[lv][pe]*|fork|vfork|clone) *\(' *.c /dev/null|egrep -v solutions/python/cowrie
)


if test -n "$banned_statements"
then
#    mv "$1" "$1.not_permitted"
cat << eof
Your program contains C features not permitted for this exercise.
$banned_statements

Your submission will not be tested.

eof
    exit 1
fi
