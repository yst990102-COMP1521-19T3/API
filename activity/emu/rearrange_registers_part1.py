#!/usr/bin/python3
import random, re, sys

for line in sys.stdin:
    line = re.sub(r'\$(\d+)', lambda m: '$' + str(random.randrange(2,32)), line)
    line = re.sub(r' (\d+)',  lambda m: ' ' + str(random.randrange(2,32)), line)
    line = re.sub(r' -(\d+)', lambda m: ' -' + str(random.randrange(2,32)), line)
    print(line, end='')