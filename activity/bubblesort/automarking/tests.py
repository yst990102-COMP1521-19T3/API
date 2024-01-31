#!/usr/bin/python3
import re
print("""
max_cpu=60
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f bubblesort.s
files=bubblesort.s

""")

tests = [
    '1 2 3 4 5 6 7 8 9 10',
    '1 2 3 4 15 6 7 8 9 5',
    '1 2 3 4 15 6 7 8 9 11',
    '1 2 3 4 5 6 17 8 9 0',
    '5 5 115 5 15 4 5 5 5 5',
    '5 5 5 115 5 4 15 15 115 4',
    '41635 63512 15589 46472 63142 38787 38676 4548 44926 40553',
    '196 32334 55783 20891 37060 61068 26512 34162 63341 17996',
    '19228 21673 61212 3803 62596 46712 1305 27879 50866 3823',
    '961 46514 32691 59140 23448 25338 49498 18314 57500 19086',
    '61168 1837 779 53764 3704 59789 49106 17791 41997 3143',
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

