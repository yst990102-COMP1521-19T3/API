#!/usr/bin/python3
print("""
max_cpu=30
compiler_args=-Dmain=_main autotest_float_bits.c float_bits.c -o float_bits
files=float_bits.c

""")
tests = [8, 3.99, 0.748, -0.749, 4.298765432e-31, 9.91234567e37,  "inf", "-inf", 0.0, -0.0, "NaN"]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} command=./float_bits {f}')

