#!/usr/bin/python3
print("""
max_cpu=30
ignore_case=1
ignore_white_space=1
ignore_blank_lines=1
command=1521 spim -f nuxi.s
files=nuxi.s

""")


def string2uint32(s):
    n = 0
    for i in range(0,4):
        n |= ord(s[i]) << (8 * i)
    return n

def reorder_bytes(bytes, unix, nuxi):
    reordered = 0
    for byte_position in range(0,4):
        new_byte_position = nuxi.index(unix[byte_position])
        byte =( bytes >> (8 * byte_position)) & 0xFF;
        reordered |= (byte << (8 * new_byte_position))
    return reordered

def int32(n):
    return n if n < 2**31 else n - 2**32

tests = [
    ('NUXI', 0xDEEDBEEF),
    ('UNXI', 0x12354678),
    ('UXNI', 0x12354678),
    ('UINX', 0x87645321),
    ('XNIU', 0x87645321),
    ('NXUI', 0xDEEDBEEF),
    ('UXNI', 0x12354678),
    ('UXIN', 0x12354678),
]

for (test_number, (nuxi, number)) in enumerate(tests):
    nuxi_number = string2uint32(nuxi)
    reordered_number = reorder_bytes(number, 'UNIX', nuxi)
    print(f"# UNIX=0x{string2uint32('UNIX'):08x}, {nuxi}=0x{string2uint32(nuxi):08x}, src=0x{number:08x}, exp=0x{reordered_number:08x}")

    print(f'{test_number} stdin="{nuxi_number}\\n{int32(number)}\\n" description="{nuxi} 0x{number:08x}" expected_stdout="Loaded: /home/cs1521/share/spim/exceptions.s\\n{int32(reordered_number)}\\n"')
