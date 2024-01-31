#!/bin/bash

banned_statements=$(
    egrep -n '"(image/png|image/jpg)"' "$1" /dev/null
)


if test -n "$banned_statements"
then
#    mv "$1" "$1.not_permitted"
cat << eof
Your program appears to hard-code mime-types:
$banned_statements

Your submission will not be tested.

eof
    exit 1
fi
