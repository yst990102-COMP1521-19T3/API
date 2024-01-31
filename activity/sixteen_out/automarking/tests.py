#!/usr/bin/python3
print("""
max_cpu=30

""")
for (test_number, number) in enumerate([0,1,-1,32767, -32768,11845,-3184,-7282,29927,31000,-31000]):
    binary = f'{(65536 + number) % 65536:016b}'
    print(f'{test_number} command=./sixteen_out {number} description="{number}" expected_stdout="{binary}\\n"')

