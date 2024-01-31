#!/usr/bin/python3
print("""
max_cpu=30
files=bit_swap.c test_bit_swap.c

""")
for (test_number, n) in enumerate([
    0x123457689ABCDEF0,
    0x0000456789A00000,
    0x1000000000000001,
    0x1111111101111111,
    0x8000000010000000,
    0x0020000200000000,
    0xFADEFADEF0DEFADE,
    0xF0F1F8FF9F6FF6FF]):
    print(f'{test_number} command=./bit_swap 0x{n:016x}')

