#!/usr/bin/python3
print("""
max_cpu=30
files=bit_count.c test_bit_count.c

""")
for (test_number, n) in enumerate([
    0x123457689ABCDEF0,
    0x0000ABCDEF000000,
    0x1000000000000001,
    0x1111111101111111,
    0x8000000010000000,
    0x0020000200000000,
    0xFADEFADEF0DEFADE,
    0xFFFFFFFFFFFFFFFF]):
    print(f'{test_number} command=./bit_count 0x{n:016x}')

