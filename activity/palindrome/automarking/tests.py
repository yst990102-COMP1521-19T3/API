#!/usr/bin/python3
import re
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f palindrome.s
files=palindrome.s

""")

tests = [
    "civic",
    "civil",
    "level",
    "lavel",
    "dodo dodo dodo odod odod odod",
    "odod odod odod dodo dodo dodo",
    "01299210",
    "019999210",
    "",
    "012999910",
    "0129999210",
    "012994210",
    "dodo dodo dodo ddd odod odod odod",
    "dodo dodo dodo ddo odod odod odod",
]
for (test_number, numbers) in enumerate(tests):
    stdin = re.sub(r' ', r'\\n', numbers)
    print(f'{test_number} stdin="{stdin}\\n" description="{numbers}"')

