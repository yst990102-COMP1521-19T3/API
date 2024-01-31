#!/usr/bin/python3
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
compiler_args=-Dmain=_main autotest_sign_flip.c sign_flip.c -o sign_flip
files=sign_flip.c

""")
tests = [4, 6, 7.99, 0.749, -0.748, -1.5, 4.198765432e-31, 9.11234567e37,  "inf", "-inf", 0.0, -0.0, "NaN"]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} command=./sign_flip {f}')

