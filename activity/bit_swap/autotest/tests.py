#!/usr/bin/python3
print("""
max_cpu=30
files=bit_swap.c test_bit_swap.c

""")
for (test_number, n) in enumerate([
    0x123456789ABCDEF0,
    0x0000000000000000,
    0x1000000000000000,
    0x1111111111111111,
    0x8000000000000000,
    0x0000000200000000,
    0xFADEFADEFADEFADE,
    0xFFFFFFFFFFFFFFFF]):
    print(f'{test_number} command=./bit_swap 0x{n:016x}')

