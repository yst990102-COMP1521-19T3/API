#! /usr/bin/env python3
tests = """
max_cpu=10
max_wall_clock=20

# have to run sanitizers separately because we are using unistd.h
compilers="1521 dcc-2.6.4 -fsanitize=valgrind -Werror"
checkers=./check_features_used.sh
# don't ask
compiler_args='`ls *.c`' -o cowrie
files=cowrie.c
command="./cowrie"
shell=1


# label=subset0


exit

cd /tmp
pwd
cd /dev
pwd

command="mkdir -p sub_dir; HOME=$(pwd)/sub_dir ./cowrie |sed 's?/tmp/.*/?/tmp/?'"
cd
pwd

command="./cowrie"
cd /this_directory_does_not_exist

# label=subset1


command="./cowrie"
/bin/echo absolute pathnames start with /

/usr/bin/echo will fail

cd /bin
./echo relative pathnames start with .

cd /dev
../bin/echo or ..

cd /usr/lib
../../bin/echo or ../..

./echo  will fail

cd /usr/lib
../bin/echo will fail

ls -s /dev/null
cd /dev
/bin/ls -s null
pwd

ls -s /dev/null

lss -s /dev/null

echo hello cowrie

false

ls -error

printf printf_lives_in_/usr/bin

cd /dev
/bin/ls -s null

cd /usr/bin
./printf this_should_run_/usr/bin_printf

cd /bin
./printf this_should_fail_because_there_is_no_/bin/printf

cd /usr/bin
../../bin/echo pathnames can contain ..

command="PATH=/usr/bin ./cowrie"
/bin/echo this will work even though /bin is not in PATH

command="PATH=/usr/bin:/usr/local/bin ./cowrie"
echo this will fail because /bin is not in PATH

command="PATH=/home/cs1521/test_bin:/usr/bin ./cowrie"
echo this should run /home/cs1521/test_bin/echo

command="PATH=/home/cs1521/test_bin:/usr/bin ./cowrie"
cd /bin
echo this should run /home/cs1521/test_bin/echo

command="PATH=/home/cs1521/test_bin:/usr/bin ./cowrie"
cd /bin
./echo this should run /bin/echo

command="export PATH=/usr/bin:/home/cs1521/test_bin; ./cowrie"
echo this should run /home/cs1521/test_bin/echo


# label=subset2


command="rm -f $HOME/.cowrie_history; ./cowrie"
echo command 1
echo command 2
history

command="rm -f $HOME/.cowrie_history; ./cowrie"
echo command 1
echo command 2
history 1

echo command 1
!0

echo command 1
!

echo command 1
!0
echo command 1
!
echo command 2
!1
!2
!3
history

command="rm -f $HOME/.cowrie_history; ./cowrie; cat -n $HOME/.cowrie_history"
echo command 1
echo command 2
echo command 3


command="rm -f $HOME/.cowrie_history; ./cowrie"
echo command 1
echo command 2
echo command 3
echo command 4
echo command 5
echo command 6
echo command 7
echo command 8
echo command 9
echo command 10
echo command 11
echo command 12
history
history 3
!5
!
!7

command="./cowrie"
history nonnumber

command="./cowrie"
history 1 1

# label=subset3

command="rm -rf tmp; mkdir tmp; cd tmp; touch a.s cat.c cat.h README readme .hidden; ../cowrie"
echo *
echo *.? *.s ???
echo *[aeio]*

command="rm -f $HOME/.cowrie_history;rm -rf tmp; mkdir tmp; cd tmp; touch a.s cat.c cat.h README readme .hidden; ../cowrie"
echo *.[ch]
!0
!
history

command="rm -f $HOME/.cowrie_history;./cowrie"
echo ~root
history

command="rm -f $HOME/.cowrie_history;./cowrie"
cd /dev
history

# label=subset4

command="./cowrie; head -3 <a.txt"
seq 10 15 >a.txt

command="seq 10 13 >b.txt; ./cowrie; head -3 <b.txt"
seq 10 15 >b.txt

command="seq 10 15 >c.txt; ./cowrie"
<c.txt head -3

command="seq 10 13 >d.txt; ./cowrie; head -5 <d.txt"
seq 42 44 >>d.txt

command="./cowrie"
seq 1 3 >e.txt
<e.txt head -2
seq 11 13 >>e.txt
<e.txt tail -4
seq 14  18 >e.txt
<e.txt head -2

history >/dev/null
</dev/null cd
pwd >a

echo hello >pwd
<pwd cat >cd
cat cd pwd >history
<history cat

# label=subset5

seq 40 50|grep 42

seq 15 45|grep 4|grep -v 42|tail -3

command="seq 1 100 >j.txt; ./cowrie; head -5 <k.txt"
<j.txt grep 4|head|tail -7 >k.txt

"""


test_number = 0
label = 'subset0'
import re
stdin = []
for  t in tests.splitlines()+[]:
    t = t.strip()

    if '=' in t or t.startswith('#'):
        if t[1:].strip().startswith('label'):
            label = t.split('=')[1].strip()
            test_number = int(label[-1:]) * 100
            continue
        print(t)
        continue

    if t:
        stdin.append(t)
        continue

    if not stdin:
        continue

    stdin_str = '\\n'.join(stdin)+'\\n'
    description = '; '.join(stdin)
    print(f'{label}_{test_number:03d} stdin="{stdin_str}" description="{description}"')
    stdin = []
    test_number += 1

