#!/usr/bin/python3
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
compiler_args=-Dmain=_main autotest_bit_rotate.c bit_rotate.c -o bit_rotate
files=bit_rotate.c

""")
tests = [
    (1, 0xa7c5),
    (11, 0xa7c5),
    (34, 0xa7c5),
    (45, 0xa7c5),
    (-2, 0xa7c5),
    (-13, 0xa7c5),
    (-24, 0xa7c5),
    (-46, 0xa7c5),
    (0, 0x1334),
    (11, 0xfaff),
    (-11, 0x0010),
    (-1111, 0x6578),
    (2222, 0x5765),
]

for (test_number, (rotate, bits)) in enumerate(tests):
    print(f'{test_number} command=./bit_rotate {rotate} 0x{bits:04x} description="bit_rotate({rotate}, 0x{bits:04x})"')

