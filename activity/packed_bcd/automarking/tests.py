#!/usr/bin/python3
print("""
max_cpu=30

""")
for (test_number, number) in enumerate([0,1,25,52,10100,242524,42425242,70000000,99997999]):
    packed_bcd = int(str(number), 16)
    print(f'{test_number} command=./packed_bcd {packed_bcd} description="0x{number:08}" expected_stdout="{number}\\n"')

