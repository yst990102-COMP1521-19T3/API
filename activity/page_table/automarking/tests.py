#! /usr/bin/env python3
tests = """
max_cpu=10
files=page_table.c
ignore_white_space=1
ignore_blank_lines=1
ignore_case=1
compare_only_characters=abcdefghijklmnopqrstuvwxyz0123456789

command=./page_table 4 6

r 0
R 0
r 0
w 0
W 0
r 0
w 0
r 1
w 1

R 0
U 0
r 0
R 0
r 0
U 0
W 5
w 5

R 0
R 1
R 2
W 3
W 4
r 0
r 1
w 4
w 3
r 0
r 2

R 0
W 1
R 2
W 3
W 4
W 5
r 2
r 3
r 0
r 5
r 3
r 4
r 2
r 2
r 2
r 4
r 2
r 5
r 5
w 2
w 4
r 3

command=./page_table 6 18
R 0
W 1
R 2
W 3
W 4
W 5
R 6
W 7
R 8
W 9
R 10
W 11
R 12
W 13
W 14
W 15
W 8
r 17
r 5
r 2
r 3
r 6
r 5
r 17
w 8
W 8
r 2
r 8
r 14
r 8
U 7
r 6
r 10
r 7
r 0
r 15
r 0
r 3
r 17
r 0
r 14
r 16
r 5
R 7
r 17
r 7
r 7
r 3
w 14
r 4
w 12

"""


import re
test_number = 0
stdin = []
for  t in tests.splitlines()+[]:
    t = t.strip()

    if '=' in t or '#' in t:
        print(t)
        continue

    if  t:
        stdin.append(t)
        continue

    if not stdin:
        continue

    stdin_str = '\\n'.join(stdin)+'\\n'
    description = ' '.join(stdin)
    description = re.sub(r'(.{42).*', r'\1 ...', description)
    print(f'{test_number:03d} stdin="{stdin_str}" description="{description}"')
    stdin = []
    test_number += 1

