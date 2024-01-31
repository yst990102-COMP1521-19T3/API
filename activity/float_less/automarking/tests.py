#!/usr/bin/python3
print("""
max_cpu=30
compiler_args=-Dmain=_main autotest_float_less.c float_less.c -o float_less
files=float_less.c

""")
tests = [(4,3.99), (0.248, 0.249), (-0.248, -0.249)]
cases = ["inf", "-inf", 0.0, -0.0, 42, -42]
tests += [(x,y) for x in cases for y in cases]
tests += [("NaN", "inf"), ("-inf", "NaN")]
done = set()
for ((f1, f2)) in tests:
    if (f1, f2) not in done and (f2, f1) not in done:
        done.add((f1,f2))
        print(f'{len(done)} command=./float_less {f1} {f2}')

