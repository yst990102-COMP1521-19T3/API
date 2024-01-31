#!/usr/bin/python3
print("""
max_cpu=30
checkers=./check_features_used.sh
compiler_args=-Dmain=_main autotest_float_print.c float_print.c -o float_print
files=float_print.c

""")
tests = [8, -42, 42, 3.99, 0.748, 0.500001, -0.749, -0.75001, 4.298765432e-31, 9.91234567e37,  "inf", "-inf", 0.0, -0.0, "NaN"]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} command=./float_print {f}')

