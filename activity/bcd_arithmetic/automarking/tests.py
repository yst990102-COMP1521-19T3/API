#!/usr/bin/python3
print("""
max_cpu=240
no_reproduce_command=1
files=bcd_arithmetic.c
compiler_args=-Dmain=_main test_bcd_arithmetic.c bcd_arithmetic.c -o test_bcd_arithmetic

""")

tests = [
    "9007199254740994 - 1",
    "9876543219876541/home/cs1521/public_html/19T3/private/_infra/scripts/321 - 1234567891213456789",
    "1000000000100000000000000 - 123450",
    "9879879879817987987987987987987987987987 - 123123123123123123123123123123123123123",
    "90071992541740993 * 1",
    "9876543219187654321 * 123456789123456789",
    "1000000001000000000000000 * 12345",
    "9879871987987987987987987987987987987987 * 123123123123123123123123123123123123123",
    "90071199254740993 // 1",
    "9876543121987654321 // 1234",
    "1000000000010000000000000 // 12345",
    "9879879879879879879879879879879879879187 // 123123123123123123123123123123",
    ]

import re
for (test_number, expression) in enumerate(tests):
    result = eval(expression)
    expression = expression.replace('//', '/')
    description = re.sub(r'(\d{64}).*', r'\1...', expression)
    print(f'{test_number} command=./test_bcd_arithmetic {expression} description="{description}" expected_stdout="{result}\\n"')

