#!/usr/bin/python3
print("""
max_cpu=30
files=short_swap.c test_short_swap.c

""")
for (test_number, n) in enumerate([0x1234, 0xFFFE,  0x0201, 0x01FF, 0x0108, 0xFF01, 0x0801]):
    print(f'{test_number} command=./short_swap 0x{n:04x} description="0x{n:04x}"')

