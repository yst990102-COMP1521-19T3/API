<?php require('../../course.php'); activity_load('labs/week08') ?>

<?= begin_document([
    'title'    => 'Week 08 Lab Exercise',
    'doctype'  => '',
    'subtitle' => 'A Minimal Shell',
]) ?>


<?= show_objectives($OBJECTIVES) ?>
<?= show_lab_admin($ACTIVITY) ?>

<aside class="tip">
<p>
Doing the exercise well and correctly
as specified will get you an A grade;
an A grade gets you full marks.
You need to do something <em>truly</em> outstanding,
above and beyond the <q>call of duty</q> to get A+;
an A+ grade also gets a small bonus.
</aside>


<h2>Background</h2>
<p>
A <dfn>shell</dfn> provides users with
an interface to the operating system:
it takes a user's input, and
determines how to fulfill those requests.
For example,
on Microsoft Windows, the shell is <q>Windows Explorer</q>;
on Apple macOS, the shell is <q>Finder</q> and <q>Dock</q>.

<p>
On most Unix-like systems,
the shell is a lot more rudimentary in its appearance.
It deals with characters on a terminal
(whether a physical device that looks like
a typewriter's worst nightmares,
or a virtual device like a <dfn>terminal emulator</dfn>),
prompting the user for input by printing out some characters,
and reading in some more characters from the user,
which it attempts to evaluate and execute as a command.
Each line of input, sometimes called a <q>command line</q>,
usually contains the name of a program,
along with some parameters that are passed to this program.
For example —

<pre>
ls -l           <span class="comment"># displays files in current directory</span>
cat -n mysh.c   <span class="comment"># show mysh.c with line numbers</span>
file mysh.c     <span class="comment"># show the file type of mysh.c</span>
wc -l Makefile  <span class="comment"># show how many lines in the Makefile</span>
/bin/ls -l      <span class="comment"># displays files in current directory</span>
</pre>


<p>
One of the things that made Unix quite unique
compared to its contemporaries was
that the shell couldn't do much by itself —
it can't list directories, or print out files —
but it <em>did</em> (and still does!) know
how to find and start other programs.
Most Unix-like systems come with
a raft of utility programs,
all filed away in a range of directories;
the shell knows a list of these,
which it calls the <code>PATH</code>,
and when a user commands the system,
the shell searches through
each of the directories in the <code>PATH</code>
for executable files matching
the name the user requested.

<p>
So, in the above list, the first and last commands
are effectively exactly the same:
the only difference is that
the last command uses the full path to
the <cite>ls(1)</cite> command,
whilst the first one doesn't.

<p>
There's several different shells
available for Unix-like systems;
they all do the same thing, more or less,
but their main difference is in
the interfaces they provide,
either in the commands and behaviours they add themselves,
or in the ways they let us interact with them.
One of the most common shells on Unix-like systems,
including most Linuxes, is <cite>bash(1)</cite>,
and it's very likely what you use on CSE.


<?= soln_io('SkpA4IVHX', null, 'SJGx8tzOQ') ?>


<h2>Setting Up</h2>
<p>
Make a new directory for this lab,
change into that directory,
and run the command:

<pre is="tty">
<kbd is="sh">unzip <a href="<?=$DIR_URL?>/lab.zip"><?=$DIR_PATH?>/lab.zip</a></kbd>
</pre>


<p>
If you're working at home,
download <code>lab.zip</code>
from the link above,
and extract it using unzip.

<p>
If you've done the above correctly,
you should now find
the following files in the directory:

<?= list_files($PROVIDED_FILES) ?>

<p>
Note that, as supplied, the program will not compile.
You will need to add some code before this happens.

<p>
To make your task simpler,
we have supplied two useful pieces:
first, a <em>tokeniser</em> that can
break a string into components,
or <dfn>tokens</dfn>, using separators.
The examples below show the function behaves.
You may find it useful to read how the function works.
Note it uses <cite>malloc(3)</cite> and <cite>strdup(3)</cite>
to create
its structures. These need to be freed at an appropriate time to
avoid memory leaks.
</p>

<figure class="text-center">
<img class="img img-fluid p-4" src="Pics/tokenise.png" />
</figure>


<h2>Exercise</h2>
<p>
You have several tasks for this lab exercise:

<h3>Task 1: Implement <code>main()</code></h3>

<p>
Implement the core part of the body of <code>main()</code>.
This requires the shell to:

<ul>
<li><p> tokenise the command line
<li><p> fork a copy of itself
<li><p> the parent shell process then waits for the child to complete
<li><p> the child shell process invokes the <code>execute()</code> function
<li><p> the parent shell process then cleans up the tokens and prints another prompt
</ul>

<p>
The arguments to <code>execute()</code> are:
the tokenised command line,
the array of path directory strings,
and the environment array.

<p>
At this point, your shell won't do much,
but you should be able to compile it and run it.

<p>
This video might help to explain the overall approach:

<?= soln_io('SkpA4IVHX', null, 'H15d95fOQ') ?>



<h3>Task 2: Implement <code>execute()</code></h3>
<p>
Implement the <code>execute()</code> function.
The <code>execute</code> function behaves as follows:

<pre>
<var>args</var> = tokenise the command line
if <var>args</var>[0] starts with '/' or '.':
    check if the file called <var>args</var>[0] is executable;
    if so, use <var>args</var>[0] as the command.
otherwise:
    for each of the directories <var>D</var> in the path,
        check if an executable file called "<var>D</var>/args[0]" exists;
        if it does, use that file name as the command.

if no executable file was found,
    print a 'command not found' message,
    and exit this child process.
otherwise:
    print the full name of the command being executed;
    use execve() to attempt to run the command with args and envp,
    if it didn't run, print an error,
    and exit this child process (as execute() is not supposed to return)
</pre>

<p>
The provided <code>isExecutable()</code> function
can check whether a given file name is executable.

<p>
This approach is not used in real shells,
because there is a <em>race condition</em>
where the executable file may have its status changed
(made non-executable) or even be removed
between you checking its status and then
attempting to execute it
(a <dfn>time-of-check vs. time-of-use</dfn> bug).
There are other functions you can use
(see, for example, the <cite>exec(3)</cite> family)
to do this more reliably.
However, the point of this lab is
to let you explicitly see
the kind of processes the shell carries out
when executing commands.

<p>
This video explains
why we need the <code>PATH</code>,
and how to use it:

<?= soln_io('SkpA4IVHX', null, 'B1n3Ijf_m') ?>

<p>
Once you have <code>execute()</code> implemented,
your shell can actually run commands!
When it's working correctly
(and after you've switched the <code>DBUG</code> flag off),
it should look like:

<pre is="tty">
<kbd is="sh">./mysh</kbd>
<kbd data-prompt="mysh$">ls -l</kbd>
Executing /bin/ls
total 28
-rw-r--r-- 1 jas jas   140 Oct  8 11:49 Makefile
-rwxr-xr-x 1 jas jas 12288 Oct  8 11:49 mysh
-rw-r--r-- 1 jas jas  3832 Oct  8 11:48 mysh.c
<kbd data-prompt="mysh$">wc -l mysh.c</kbd>
Executing /usr/bin/wc
148 mysh.c
<kbd data-prompt="mysh$">dud command with many args</kbd>
dud: Command not found
<kbd data-prompt="mysh$">cp mysh.c xyz</kbd>
Executing /bin/cp
<kbd data-prompt="mysh$">ls -l</kbd>
Executing /bin/ls
total 32
-rw-r--r-- 1 jas jas   140 Oct  8 11:49 Makefile
-rwxr-xr-x 1 jas jas 12288 Oct  8 11:49 mysh
-rw-r--r-- 1 jas jas  3832 Oct  8 11:48 mysh.c
-rw-r--r-- 1 jas jas  3832 Oct  8 11:50 xyz
<kbd data-prompt="mysh$"><i>^D</i></kbd>
<kbd is="sh"></kbd><span class="comment">... back to the real shell</span>
</pre>

<p>
Obviously the file sizes, dates and user and group
will be different for you.


<h3>Task 3: Implementing <code>cd</code> and <code>pwd</code></h3>
<p>
Some commands won't work the same in <code>mysh</code>
as they do in a regular shell;
the most notable case is <code>cd</code>,
which isn't actually a program.
If it were implemented as a program,
changing directories would only happen
within the child process,
and therefore would have no effect.

<p>
Instead, <code>cd</code> is implemented as
a <dfn>shell built-in</dfn>:
a directive to the shell itself.
Shell built-ins take the place of
a call to <code>execute()</code>:
see, for example,
how <code>exit</code> (another built-in)
is handled in the <code>main()</code> loop.

<p>
We could check if the command was <code>cd</code>
in a similar way,
although we might like to check
after the command line has been tokenised,
so we can get the directory the user wants to change to.
We also need to call the <cite>chdir(2)</cite> system call
with the name of the directory we want to change to.

<p>
<cite>pwd(1)</cite> is also occasionally implemented as a built-in:
it's significantly faster to <q>just</q> print it out
than it is to spawn a new process to print it out.
As with <code>cd</code>, implement a built-in <cite>pwd(1)</cite>;
you'll need to use either <cite>getcwd(3)</cite>.

<p>
Once both are implemented:

<pre is="tty">
<kbd data-prompt="mysh$">pwd</kbd>
/Users/jas/cs1521/labs/week08/files
<kbd data-prompt="mysh$">cd ..</kbd>
<kbd data-prompt="mysh$">pwd</kbd>
/Users/jas/cs1521/labs/week08
<kbd data-prompt="mysh$">cd</kbd>
<kbd data-prompt="mysh$">pwd</kbd>
/Users/jas
<kbd data-prompt="mysh$">cd /</kbd>
<kbd data-prompt="mysh$">pwd</kbd>
/
</pre>

<p>
Again, the paths will differ for you.
<code>cd</code> with no arguments
should take you to your home directory;
you can use <code>getenv("HOME")</code> to get that.

<?= begin_challenges() ?>
<?= begin_challenge() ?>
<p><?= challenge_rating(1) ?>
<q>fork was a clever hack
for machines and programs of the 1970s
that has long outlived its usefulness
and is now a liability,</q>
according to Andrew Baumann,
a UNSW CSE alumnus, now at Microsoft Research;
and this isn't an uncommon view
amongst operating systems researchers.
Read Baumann's paper,
<a href="https://dl.acm.org/citation.cfm?doid=3317550.3321435">
<q>A fork() in the road</q> (doi:10.1145/3317550.3321435)</a>,
from the <a href="https://hotos19.sigops.org/">2019 Workshop on Hot Topics in Operating Systems</a>;
then modify your shell
to use <cite>posix_spawn(3)</cite> instead.
<?= end_challenge() ?>

<?= begin_challenge() ?>
<p><?= challenge_rating(2) ?>
Most shells give us
powerful line editing facilities:
if we make a mistake,
we can usually amend it
without having to erase
all the characters we've already typed.
Our shell is presently very unforgiving —
we cannot do much to fix up our mistakes —
so enhance it to allow this.
You may like to investigate either
the <cite>readline(3)</cite> or Curses libraries;
or you could send escape sequences to the terminal yourself.
Closely related to this is managing history:
being able to remember commands that were run,
and recall (and change or execute) them.
<?= end_challenge() ?>

<?= begin_challenge() ?>
<p><?= challenge_rating(3) ?>
One feature of the shell we use fairly frequently
is input and output <dfn>redirection</dfn>:
instead of reading from or writing to the terminal,
we can direct programs to
take input from, and send output to,
files that we specify on the command line —
or to and from other programs.

<p>
Some simple redirections:

<pre is="tty">
      <span class="comment">... write output to xyz</span>
<kbd data-prompt="mysh$">cat mysh.c &gt; xyz</kbd>
      <span class="comment">... read input from xyz</span>
<kbd data-prompt="mysh$">cat &lt; xyz</kbd>
      <span class="comment">... read input from xyz and write output to /dev/null</span>
<kbd data-prompt="mysh$">cat &lt; xyz &gt; /dev/null</kbd>
</pre>

<p>
To connect programs up, we use pipes.
We use <cite>pipe(2)</cite> to create
a connected pair of file descriptors:
anything written to the second
can then be read from the first;
and <cite>dup2(2)</cite> lets us connect
two file descriptors together in a process.

<pre is="tty">
      <span class="comment">... ls' stdout is cat's stdin</span>
<kbd data-prompt="mysh$">ls | cat</kbd>
      <span class="comment">... redirections still work</span>
<kbd data-prompt="mysh$">ls | cat > /dev/null</kbd>
      <span class="comment">... and pipes chain, too</span>
<kbd data-prompt="mysh$">find ~ | sort | grep .c$</kbd>
</pre>

<p>
And once you've got that working,
these harder redirections should be a piece of cake.

<pre is="tty">
      <span class="comment">... write fd 2 (stderr) to /dev/null</span>
<kbd data-prompt="mysh$">cat nonexistent 2&gt; /dev/null</kbd>
      <span class="comment">... open fd 3 to /dev/null; direct fd 1 (stdout) there</span>
<kbd data-prompt="mysh$">cat xyz 3&gt; /dev/null 1&gt;&amp;3</kbd>
      <span class="comment">... close fd 0 (stdin); upset cat(1)</span>
<kbd data-prompt="mysh$">cat <&amp;-</kbd>
</pre>
<?= end_challenge() ?>

<?= begin_challenge() ?>
<p><?= challenge_rating(4) ?>
<dfn>Job control</dfn> is a shell's ability
to suspend, resume, or background commands.
Implement job control in your shell,
something a little like:

<pre is="tty">
<kbd data-prompt="mysh$">gedit</kbd>
<kbd><i>^Z</i></kbd>    <span class="comment">... suspend a job</span>
      <span class="comment">... puts a background job into the foreground</span>
<kbd data-prompt="mysh$">fg</kbd>
      <span class="comment">... puts a suspended job into the background</span>
<kbd data-prompt="mysh$">bg</kbd>
      <span class="comment">... start a job in the background</span>
<kbd data-prompt="mysh$">gedit &amp;</kbd>
      <span class="comment">... list the jobs in the background</span>
<kbd data-prompt="mysh$">jobs</kbd>
</pre>

<p>
You may find it useful to read about
sending signals with <cite>kill(2)</cite> and
handling signals with <cite>sigaction(2)</cite>.
<?= end_challenge() ?>

<?= begin_challenge() ?>
<p><?= challenge_rating(5) ?>
Implement the rest of <cite>sh(1)</cite>'s built-in commands
(such as <code>alias</code>, <code>ulimit</code>, <code>umask</code>, etc.)
and scripting language (including keywords like
<code>if</code>, <code>then</code>, <code>else</code>, <code>fi</code>, etc.).
You may find it useful to read about
<cite>lex(1)</cite>,
which generates tokenisers
(sometimes known as <dfn>lexical analysers</dfn>)
based on specified rules;
and <cite>yacc(1)</cite>,
which similarly generates parsers.
<br><small>(If you're enjoying this challenge, why not try
<a href="https://www.handbook.unsw.edu.au/undergraduate/courses/current/COMP3131/" title="Programming Languages and Compilers">COMP3131</a> or
<a href="https://www.handbook.unsw.edu.au/undergraduate/courses/current/COMP3161/" title="Concepts of Programming Languages">COMP3161</a>?)</small>
<?= end_challenge() ?>
<?= end_challenges() ?>


<?= show_submission($ACTIVITY) ?>
<?= begin_comment() ?>
<p>
Have fun, <i>jas</i>
<?= end_comment() ?>
<?= end_document() ?>
