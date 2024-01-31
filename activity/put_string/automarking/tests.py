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
    'helloo',
    'test1234',
    'good bye now',
    '',
]
for (test_number, argument) in enumerate(tests):
    print(f'{test_number} command="./put_string \'{argument}\'"')


