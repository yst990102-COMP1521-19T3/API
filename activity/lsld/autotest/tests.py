#!/usr/bin/python3
import re
print("""
max_cpu=30
checkers=./check_features_used.sh
shell=1
files=lsld.c
program=lsld

""")


tests = [
    'chmod 644 p1 >p1',
    'chmod 755 p2 >p2',
    'chmod 666 p3 >p3',
    'chmod 223 p4 >p4',
    'mkdir -p -m 700 p5',
    'mkdir -p -m 727 p6',
]

for (test_number, create_file) in enumerate(tests):
    file = create_file[-2:0]
    command = f"{create_file};ls -ld {file} >tmp1; ./lsld >tmp2; diff -b tmp1 tmp2 && echo identical"
    print(f'{test_number} command="{command}\\n"')
test_number += 1
create_file = '; '.join(tests)
file = 'p?'
command = f"{create_file};ls -ld {file} >tmp1; ./lsld {file} >tmp2; diff -b tmp1 tmp2 && echo identical"
print(f'{test_number} command="{command}\\n"')
