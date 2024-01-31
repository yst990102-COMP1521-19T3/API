#!/usr/bin/python3
print("""
max_cpu=30
compiler_args=-Dmain=_main autotest_sign_flip.c sign_flip.c -o sign_flip
files=sign_flip.c

""")
tests = [8, 3.99, 0.748, -0.749, 4.298765432e-31, 9.91234567e37,  "inf", "-inf"]
for (test_number, f) in enumerate(tests):
    print(f'{test_number} command=./sign_flip {f}')

