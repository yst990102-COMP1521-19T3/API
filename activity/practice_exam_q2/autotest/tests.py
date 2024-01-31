#!/usr/bin/python3
print("""
max_cpu=30
files=practice_exam_q2.c test_practice_exam_q2.c

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
    print(f'{test_number} command=./practice_exam_q2 0x{n:016x}')

