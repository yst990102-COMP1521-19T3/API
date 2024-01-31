#!/usr/bin/python3
print("""
max_cpu=30

""")
for (test_number, number) in enumerate([0,1,-1,32767, -32768,21845,-2184,-7282,29127,30000,-30000]):
    binary = f'{(65536 + number) % 65536:016b}'
    print(f'{test_number} command=./sixteen_in {binary} description="{binary}" expected_stdout="{number}\\n"')

