#!/usr/bin/python3
print("""
max_cpu=120
no_reproduce_command=1
files=bcd_arithmetic.c
compiler_args=-Dmain=_main test_bcd_arithmetic.c bcd_arithmetic.c -o test_bcd_arithmetic

""")

tests = [
    "34159 - 27818",
    "9007199254740994 - 1",
    "987654321987654321 - 123456789123456789",
    "1000000000000000000000000 - 12345",
    "987987987987987987987987987987987987987 - 123123123123123123123123123123123123123",
    "6"*1025 + " - " + "4"*1025,
    "42 * 24",
    "34159 * 27818",
    "9007199254740993 * 1",
    "987654321987654321 * 123456789123456789",
    "1000000000000000000000000 * 12345",
    "987987987987987987987987987987987987987 * 123123123123123123123123123123123123123",
    "6"*1025 + " * " + "4"*1025,
    "42 // 6",
    "34159 // 278",
    "9007199254740993 // 1",
    "987654321987654321 // 1234",
    "1000000000000000000000000 // 12345",
    "987987987987987987987987987987987987987 // 123123123123123123123123123123",
    "6"*1025 + " // " + "4"*512,
    ]

import re
for (test_number, expression) in enumerate(tests):
    result = eval(expression)
    expression = expression.replace('//', '/')
    description = re.sub(r'(\d{64}).*', r'\1...', expression)
    print(f'{test_number} command=./test_bcd_arithmetic {expression} description="{description}" expected_stdout="{result}\\n"')

