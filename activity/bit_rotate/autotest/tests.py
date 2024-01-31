#!/usr/bin/python3
print("""
max_cpu=30
max_cpu=30
compiler_args=-Dmain=_main autotest_bit_rotate.c bit_rotate.c -o bit_rotate
files=bit_rotate.c

""")
tests = [
    (1, 0xa7c5),
    (12, 0xa7c5),
    (33, 0xa7c5),
    (44, 0xa7c5),
    (-1, 0xa7c5),
    (-12, 0xa7c5),
    (-23, 0xa7c5),
    (-45, 0xa7c5),
    (0, 0x1234),
    (11, 0xffff),
    (-11, 0x0000),
    (-1111, 0x5678),
    (2222, 0x5768),
]

for (test_number, (rotate, bits)) in enumerate(tests):
    print(f'{test_number} command=./bit_rotate {rotate} 0x{bits:04x} description="bit_rotate({rotate}, 0x{bits:04x})"')

