#!/usr/bin/python3
import re
print("""
max_cpu=30
checkers=./check_features_used.sh
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
shell=1
files=lsld.c
program=lsld

""")

tests = [
    'chmod 624 p1 >p1',
    'chmod 775 p2 >p2',
    'chmod 665 p3 >p3',
    'chmod 224 p4 >p4',
    'mkdir -p -m 770 p5',
    'mkdir -p -m 757 p6',
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
