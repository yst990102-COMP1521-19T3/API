#!/usr/bin/python3
print("""
max_cpu=30

""")
for (test_number, number) in enumerate([0,1,24,42,90,99]):
    bcd = (number // 10) * 256 + number % 10
    print(f'{test_number} command=./bcd {bcd} description="0x{bcd:04x}" expected_stdout="{number}\\n"')

