// mysh.c ... a minimal shell
// Started by John Shepherd, October 2017
// Completed by <<YOU>>, July 2019

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#define DEFAULT_PATH "/bin:/usr/bin"
#define DBUG

static void runProcess (char **args, char **path);
static void reportStatus (pid_t, int);
static void execute (char **, char **, char **) __attribute__((noreturn));
static bool isExecutable (char *);
static char **tokenise (const char *, const char *);
static void freeTokens (char **);
static char *trim (char *);
static size_t strrspn (const char *, const char *);


// Environment variables are pointed to by `environ', an array of
// strings terminated by a NULL value -- something like:
//     { "VAR1=value", "VAR2=value", NULL }
extern char **environ;

int main (void)
{
	// grab the `PATH' environment variable;
	// if it isn't set, use the default path defined above
	char *pathp;
	if ((pathp = getenv ("PATH")) == NULL)
		pathp = DEFAULT_PATH;
	char **path = tokenise (pathp, ":");

#ifdef DBUG
	for (int i = 0; path[i] != NULL; i++)
		printf ("dir[%d] = %s\n", i, path[i]);
#endif

	// main loop: print prompt, read line, execute command
	char line_[BUFSIZ];
	printf ("mysh$ ");
	while (fgets (line_, BUFSIZ, stdin) != NULL) {
		char *line = trim (line_); // remove leading/trailing space
		char **args = tokenise (line, " ");

		if (args[0] == NULL) {
			freeTokens (args);
			printf ("mysh$ ");
			continue;
		}

		if (strcmp (args[0], "exit") == 0) {
			freeTokens (args); break;

		} else if (strcmp (args[0], "cd") == 0) {
			// cd <path> => chdir (path)
			// cd        => chdir ("~")
			char *dir = args[1] == NULL ? getenv ("HOME") : args[1];
			if (chdir (dir) < 0) warn ("%s", args[1]);

		} else if (strcmp (args[0], "pwd") == 0) {
			puts (getcwd (line_, BUFSIZ));

		} else {
			runProcess (args, path);
		}

		freeTokens (args);
		printf ("mysh$ ");
	}

	printf ("\n");

	freeTokens (path);

	return EXIT_SUCCESS;
}

static void runProcess (char **args, char **path)
{
	pid_t pid;   // pid of child process
	int stat;	 // return status of child

	switch (pid = fork()) {
	case -1: warn ("fork"); break;
	case  0: execute (args, path, environ);
	default:
		if (waitpid (pid, &stat, 0) < 0)
			warn ("waitpid");
		else
			reportStatus (pid, stat);
	}
}

static void reportStatus (pid_t pid, int stat)
{
	if (WIFEXITED (stat) && WEXITSTATUS (stat) != 0)
		printf ("[process %d exited with status %d]\n",
			pid, WEXITSTATUS(stat));
	if (WIFSIGNALED (stat))
		printf ("[process %d received signal %d%s]\n",
			pid, WTERMSIG(stat),
			WCOREDUMP(stat) ? "; core dumped" : "");
}

// execute: run a program, given command-line args, path and envp
static void execute (char **args, char **path, char **envp)
{
	assert (args != NULL && args[0] != NULL);
	assert (path != NULL);

	char *exe = NULL;
	char *pname = args[0];
	size_t pnLen = strlen (pname);

	if (pname[0] == '.' || pname[0] == '/') {
		exe = pname;
	} else for (char **dir = path; *dir != NULL; dir++) {
		char *p;
		size_t pLen = strlen (*dir) + 1 + pnLen + 1;
		if ((p = malloc (pLen)) == NULL)
			err (EX_OSERR, "couldn't allocate");
		stpcpy (stpcpy (stpcpy (p, *dir), "/"), pname);
		if (isExecutable (p)) { exe = p; break; }
		free (p);
	}

	if (exe == NULL) {
		errno = ENOENT;
		err (EX_NOINPUT, "%s", pname);
	}

	printf ("Executing %s\n", exe);
	execve (exe, args, envp);

	// Either we've `execve(2)'d successfully and our process and
	// address space no longer exist, or it failed and we need to report
	// that failure and bail out.
	err (EX_OSERR, "%s", pname);
}

/// isExecutable: check whether this process can execute a file
static bool isExecutable (char *cmd)
{
	struct stat s;
	// must be accessible
	if (stat (cmd, &s) < 0) return false;
	// must be a regular file
	if (! S_ISREG (s.st_mode)) return false;
	// if it's owner executable by us, ok
	if (s.st_uid == getuid () && s.st_mode & S_IXUSR) return true;
	// if it's group executable by us, ok
	if (s.st_gid == getgid () && s.st_mode & S_IXGRP) return true;
	// if it's other executable by us, ok
	if (s.st_mode & S_IXOTH) return true;
	// otherwise, no, we can't execute it.
	return false;
}

/// tokenise: split a string around a set of separators
/// create an array of separate strings
/// final array element contains NULL
static char **tokenise (const char *str_, const char *sep)
{
	char **results  = NULL;
	size_t nresults = 0;

	// strsep(3) modifies the input string and the pointer to it,
	// so make a copy and remember where we started.
	char *str = strdup (str_);
	char *tmp = str;

	char *tok;
	while ((tok = strsep (&str, sep)) != NULL) {
		// "push" this token onto the list of resulting strings
		results = realloc (results, ++nresults * sizeof (char *));
		results[nresults - 1] = strdup (tok);
	}

	results = realloc (results, ++nresults * sizeof (char *));
	results[nresults - 1] = NULL;

	free (tmp);
	return results;
}

/// freeTokens: free memory associated with array of tokens
static void freeTokens (char **toks)
{
	for (int i = 0; toks[i] != NULL; i++)
		free (toks[i]);
	free (toks);
}

/// trim: remove leading and trailing whitespace from a string
static char *trim (char *str)
{
	char *space = " \r\n\t";
	str[strrspn (str, space) + 1] = '\0'; // skip trailing whitespace
	str = &str[strspn (str, space)];      // skip leading whitespace
	return str;
}

/// strrspn: find a suffix substring made up of any of `set'.
/// like `strspn(3)', except from the end of the string.
static size_t strrspn (const char *str, const char *set)
{
	size_t len;
	for (len = strlen (str); len != 0; len--)
		if (strchr (set, str[len]) == NULL)
			break;
	return len;
}
