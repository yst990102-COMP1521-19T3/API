#!/usr/bin/python3
tests = """
ax_cpu=30
checkers=./check_features_used.sh
compiler_args=-Dmain=_main autotest_get_string.c get_string.c -o get_string
files=get_string.c
shell=1

16 hello-world
8 hello-world
1 hello-world
32 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
64 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
"""

test_number = 1
for  t in tests.splitlines():
    t = t.strip()
    if not t or '=' in t or '#' in t:
        print(t)
        continue
    t = t.split()
    buffer_len = t[0]
    input = " ".join(t[1:])
    print('{0} command=./get_string {1} stdin="{2}\\n" description=\'get_string size={1} input="{2}"\''.format(test_number, buffer_len,input))
    test_number += 1
