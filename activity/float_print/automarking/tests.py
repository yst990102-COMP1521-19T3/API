#!/usr/bin/python3
print("""
max_cpu=30
checkers=./check_features_used.sh
compiler_args=-Dmain=_main autotest_float_print.c float_print.c -o float_print
files=float_print.c

""")
tests = [1.5, -2.25, 3.01, 4.99, 0.748, 0.2500001, -0.249, -0.25001, 4.228765432e-32, 9.1234567e36,  "inf", "-inf", 0.0, -0.0, "NaN"]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} command=./float_print {f}')

