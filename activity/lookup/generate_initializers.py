#!/usr/bin/python3
import random

COLS = 24
ROWS = 42

initializers = [[str(random.randrange(1, 10)) for c in range(COLS)] for r in range(ROWS)]

for row in initializers:
    print('    {' + ','.join(row) +'},')

for row in initializers:
    print('    .word ' + ' '.join(row))
