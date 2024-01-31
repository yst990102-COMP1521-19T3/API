#!/usr/bin/python3
print("""
max_cpu=30
files=short_swap.c test_short_swap.c

""")
for (test_number, n) in enumerate([0x4321, 0xFFEF,  0x0102, 0x01EF, 0x0801, 0xFE01, 0x0802]):
    print(f'{test_number} command=./short_swap 0x{n:04x} description="0x{n:04x}"')

