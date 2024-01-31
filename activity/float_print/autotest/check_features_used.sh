#!/bin/bash

banned_statements=$(
    egrep -n 'printf|double' "$1" /dev/null
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
