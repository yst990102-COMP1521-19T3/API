#!/usr/bin/python3
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
compiler_args=-Dmain=_main autotest_float_exp.c float_exp.c -o float_exp
files=float_exp.c

""")
tests = [4, 6, 7.99, 0.749, -0.748, -1.5, 4.198765432e-31, 9.11234567e37,  "inf", "-inf", 0.0, -0.0, "NaN"]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} command=./float_exp {f}')

