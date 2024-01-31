#!/usr/bin/python3
print("""
max_cpu=120
no_reproduce_command=1
files=bcd_add.c
compiler_args=-Dmain=_main test_bcd_add.c bcd_add.c -o test_bcd_add

""")

tests = [
    (341591, 278181),
    (9007199254740992, 1),
    (1234567891234567891, 9876543219876543212),
    (10000000000000000000000000, 123450),
    (123123123123123123123143123123123123123123123123, 987987987987987987947987987987987987987987987),
    (int("6"*1025), int("4"*1025)),
    ]

for (test_number, (left,right)) in enumerate(tests):
    left_description = str(left)
    right_description = str(right)
    if len(left_description) > 64:
        left_description = left_description[0:64] + "..."
    if len(right_description) > 64:
        right_description = right_description[0:64] + "..."
    description = left_description + " " + right_description
    print(f'{test_number} command=./test_bcd_add {left} {right} description="{description}" expected_stdout="{left + right}\\n"')

