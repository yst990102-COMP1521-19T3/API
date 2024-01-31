#!/usr/bin/python3
print("""
max_cpu=30

""")
for (test_number, number) in enumerate([0,1,24,42,10000,242424,42424242,90000000,99999999]):
    packed_bcd = int(str(number), 16)
    print(f'{test_number} command=./packed_bcd {packed_bcd} description="0x{number:08}" expected_stdout="{number}\\n"')

