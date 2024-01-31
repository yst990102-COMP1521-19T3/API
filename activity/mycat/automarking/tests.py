#!/usr/bin/python3
import glob

def main():
    print("""
max_cpu=30

""")
    for i in range(1,5 ):
        for (test_number, (description, stdin)) in enumerate(test_files):
            stdin = stdin.replace("\n", "\\n")
            print(f'cat{i}_{test_number} command=./cat{i} description="{description}" stdin="{stdin}"')
    print("""
cat4_a command=./cat4 1.txt description="empty file"
cat4_b command=./cat4 2.txt description="simple file with two lines"
cat4_c command=./cat4 3.txt 2.txt description="two files"
cat4_d command=./cat4 1.txt 2.txt 3.txt 4.txt 5.txt 6.txt description="two files"

""")

test_files = [
    ("no input", ""),
    ("1 line of input", "A simple file with one line\n"),
    ("2 lines of input", "A simple file\nwith two lines\n"),
    ("3 lines of input", "A simple file\nwith three\nlines\n"),
    ("3 empty lines", "\n\n\n"),
    ("4 empty lines", "\n\n\n\n"),
    ("4 lines of input", """abcdefghijklmnopqrstuvwayz
01234567890
abcdefghijklmnopqrstuvwayz
01234567890
abcdefghijklmnopqrstuvwayz
01234567890
"""),
    ("4 empty lines", "\n\n\n\n"),
    ("5 lines of input", """abcdefghijklmnopqrstuvwayz
01234567890
abcdefghijklmnopqrstuvwayz
abcdefghijklmnopqrstuvwayz
01234567890
abcdefghijklmnopqrstuvwayz
01234567890
"""),
    ("3 long lines of input", "\n".join(["1"*100, "2"*200, "3"*300]) + "\n"),
    ("3 long lines of input - no newline on last line", "\n".join(["1"*100, "2"*200, "3"*300])),
    ("1 huge lines of input", "abcdefghijklmnopqrstuvwxyz"*1000 + "\n"),
    ("long line with no new line", "abcdefghijklmnopqrstuvwxyz"*100),
#   ("non ASCII bytes", ''.join(chr(i) for i in range(0,256))),
]

main()