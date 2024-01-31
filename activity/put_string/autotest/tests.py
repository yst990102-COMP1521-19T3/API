#!/usr/bin/python3
import re
print("""
max_cpu=30
checkers=./check_features_used.sh
compiler_args=-Dmain=_main autotest_put_string.c put_string.c -o put_string
files=put_string.c
shell=1

""")

tests = [
    'hello',
    'test123',
    'good bye',
    '',
]
for (test_number, argument) in enumerate(tests):
    print(f'{test_number} command="./put_string \'{argument}\'"')


