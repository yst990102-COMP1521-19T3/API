<?php require("../../course.php"); ?>
<?php require("../../lib/geshi.php"); ?>
<? $dir = HOMEDIR."/assignments/assign2"; $web = HOME."/assignments/assign2"; ?>
<?=startPage("Assignment 2","","Testing Suggestions")?>

<h2>Testing <code>mymysh</code></h2>
<p>
Supplying a set of tests and definitive expected outputs is tricky
for this assignment, because <tt>mymysh</tt> runs in your environment
and produces output which is dependent on your environment.
Of course, when we run our auto-testing, it will be in our environment
and we can control what the expected output should be.
</p>
<p>
Before you run the tests below, you should remove your history
file, e.g.
</p>
<pre>
$ rm ~/.mymysh_history
</pre>
<p>
At least then, the history outputs should match what we give below.
</p>
<p>
The next thing to do is to change into the directory containing
your <tt>mymysh</tt> executable.
</p>
<p>
You should also create some small text files that you can use for
running commands on.
The following command will create three text files:
</p>
<pre>
$ unzip <?="$dir"?>/files.zip
Archive:  <?="$dir"?>/files.zip
 extracting: abc.txt                 
 extracting: def.txt                 
  inflating: ghi.txt         
</pre>
<p>
This will give you at least a partly known environment to play with.
</p>
<p>
Now run your <tt>mymysh</tt> and try the following.
We indicate the kind of output you should get in
<span class="green">green font</span>.
If you don't get exactly this output, think about whether there
is something different in your environment that might be causing
the difference.
Comments about possible variations or possible errors are in
<span class="grey">grey font</span>.
These comments are
<em>not</em> expected output from your <tt>mymysh</tt>.
</p>
<p>
It would be worth running two terminal windows, once running
<tt>mymysh</tt> and one running <tt>~cs1521/bin/mymysh</tt>.
You can then compare the output from your shell to the
reference one, keeping in mind that you need to ensure that
they're both looking at the same directory, and will have
different command histories.
</p>

<h2>Testing Examples</h2>
<p>
The assume that you have done the setting up as described above.
</p>
<pre>
$ <b>./mymysh</b>
mymysh$ <b>h</b> 
<span class="grey"># should produce no output if you removed the history file as we asked</span>
mymysh$ pwd
<span class="grey"># whatever directory your mymysh executable is in</span>
mymysh$ ls *.txt
<span class="green">Running /bin/ls ...
--------------------
abc.txt  def.txt  ghi.txt
--------------------
Returns 0</span>
<span class="grey"># may show other files if you already had them in this directory</span>
mymysh$ <b>ls *.txt &gt; ls.out</b>
<span class="green">Running /bin/ls ...
--------------------
--------------------
Returns 0</span>
<span class="grey"># should create a new file called "ls.out"</span>
mymysh$ <b>h</b>
<span class="green">   1  h
   2  pwd
   3  ls *.txt
   4  ls *.txt &gt; ls.out</span>
<span class="grey"># assuming that you removed the history file before running mymysh</span>
mymysh$ <b>cat ls.out</b>
<span class="green">Running /bin/cat ...
--------------------
abc.txt
def.txt
ghi.txt
--------------------
Returns 0</span>
<span class="grey"># should contain the same files as appeared in the original ls command</span>
<span class="grey"># not that the file names appear on separate lines when ls writes to a file </span>
mymysh$ <b>cat -n &lt; *.out</b>
<span class="green"> Running /bin/cat ...
--------------------
     1	abc.txt
     2	def.txt
     3	ghi.txt
--------------------
Returns 0 </span>
<span class="grey"># this command will fail if you happen to have other *.out files in your directory</span>
mymysh$ <b>cat &lt; abc.txt def.txt</b>
<span class="green">Invalid i/o redirection</span>
mymysh$ <b>cat &lt; *.txt</b>
<span class="green">Invalid i/o redirection</span>
mymysh$ <b>cat &lt; ls.out &gt; xyz.out</b>
<span class="green">Invalid i/o redirection</span>
<span class="grey"># this should not create a file called "xyz.out"</span>
mymysh$ <b>ls -l ~cs1521/web/18s2/assignments</b>
<span class="green">Running /bin/ls ...
--------------------
total 8
drwxr-xr-x 5 cs1521 cs1521 4096 Aug 27 23:19 assign1
drwxr-xr-x 3 cs1521 cs1521 4096 Oct  7 11:33 assign2
--------------------
Returns 0
</span>
<span class="grey"># the dates may be different if we happen to change them</span>
mymysh$ <b>cd ~cs1521/web/18s2/assignments</b>
<span class="green">/tmp_amd/ravel/export/ravel/3/cs1521/public_html/18s2/assignments</span>
<span class="grey"># the above is the file name I get; you may get something different</span>
<span class="grey"># however, it should end in "18s2/assignments"</span>
mymysh$ <b>ls -l</b>
<span class="green">Running /bin/ls ...
--------------------
total 8
drwxr-xr-x 5 cs1521 cs1521 4096 Aug 27 23:19 assign1
drwxr-xr-x 3 cs1521 cs1521 4096 Oct  7 11:33 assign2
--------------------
Returns 0
</span>
<span class="grey"># should be same output as from the earlier ls command</span>
mymysh$ <b>cat assign1</b>
<span class="green">Running /bin/cat ...
--------------------
cat: assign1: Is a directory
--------------------
Returns 1</span>
<span class="grey"># the error message is coming from the /bin/cat command</span>
mymysh$ <b>h</b>
<span class="green">   1  h
   2  pwd
   3  ls *.txt
   4  ls *.txt &gt; ls.out
   5  h
   6  cat ls.out
   7  cat -n < *.out
   8  ls -l ~cs1521/web/18s2/assignments
   9  cd ~cs1521/web/18s2/assignments
  10  ls -l
  11  cat assign1</span>
<span class="grey"># assuming that you removed the history file before running mymysh</span>
mymysh$ <b>cd <i>TheDirectoryWhereMymyshIsLocated</i></b>
<span class="grey"># shows the name of the directory you just cd'd back to</span>
mymysh$ <b>nothing</b>
<span class="green">nothing: Command not found</span>
<span class="grey"># unless you happen to have a command called "nothing" in your PATH</span>
mymysh$ <b>touch nonexec</b>
<span class="green">Running /usr/bin/touch ...
--------------------
--------------------
Returns 0 </span>
mymysh$ <b>chmod 111 nonexec</b>
<span class="green">Running /bin/chmod ...
--------------------
--------------------
Returns 0</span>
mymysh$ <b>./nonexec</b>
<span class="green">Running ./nonexec ...
--------------------
./nonexec: unknown type of executable
--------------------
Returns 255</span>
<span class="grey">zzz</span>
mymysh$ <b>./mymysh</b>
<span class="grey"># run mymysh from inside mymysh</span>
<span class="green">Running ./mymysh ...
--------------------
mymysh$ <b>echo hello</b>
Running /bin/echo ...
--------------------
hello
--------------------
Returns 0
mymysh$ <b>exit</b>

--------------------
Returns 0</span>
<span class="grey"># the final Return 0 is from the mymysh that you ran inside mymy</span>
mymysh$ <b>exit</b>

<span class="grey"># quits mymysh, returning you to your regular shell</span>
$
</pre>
<p>
Some more wildcard tests from Shanush.
Run all of these commands in <tt>mymysh</tt>
</p>
<pre>
mkdir aTestFolder
cd aTestFolder
touch q123123.c q1.c q2.c q3.c q4.c q5.c q21.c q22.c q23.c q31.c q33.c q34.c random.c
ls
ls q*.c
ls q?.c
ls q??.c
ls q?.c q??.c
ls q[2-4].c
ls q[2][1-5].c
ls q[1-9][1-9].c
ls q???.c
cd ..
rm -r aTestFolder
exit
</pre>

<?=endPage()?>
