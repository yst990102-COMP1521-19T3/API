// myls.c ... my very own "ls" implementation

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXDIRNAME 256
#define MAXFNAME   256
#define MAXNAME    24

char *rwxmode (mode_t, char *);
char *username (uid_t, char *);
char *groupname (gid_t, char *);

int main (int argc, char *argv[])
{
	// string buffers for various names
	// char uname[MAXNAME+1]; // UNCOMMENT this line
	// char gname[MAXNAME+1]; // UNCOMMENT this line
	// char mode[MAXNAME+1]; // UNCOMMENT this line

	// collect the directory name, with "." as default
	char dirname[MAXDIRNAME] = ".";
	if (argc >= 2) {
		/// NOTE: strncpy(3) is unsafe, and may not produce a string.
		/// You nearly always want (non-standard) strlcpy(3) instead.
		strncpy (dirname, argv[1], MAXDIRNAME);
		dirname[MAXDIRNAME - 1] = '\0';
	}

	// check that the name really is a directory
	struct stat info;
	if (stat (dirname, &info) < 0)
		perror (dirname), exit (71);

	if (! S_ISDIR (info.st_mode)) {
		errno = ENOTDIR;
		perror (dirname), exit (65);
	}

	// open the directory to start reading
	// DIR *df; // UNCOMMENT this line
	// ... TODO ...

	// read directory entries
	// struct dirent *entry; // UNCOMMENT this line
	// ... TODO ...

	// finish up
	// closedir(df); // UNCOMMENT this line

	return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode (mode_t mode, char *str)
{
	// ... TODO ...
	return NULL;
}

// convert user id to user name
char *username (uid_t uid, char *name)
{
	struct passwd *uinfo = getpwuid (uid);
	if (uinfo != NULL)
		snprintf (name, MAXNAME, "%s", uinfo->pw_name);
	else
		snprintf (name, MAXNAME, "%d?", (int) uid);
	return name;
}

// convert group id to group name
char *groupname (gid_t gid, char *name)
{
	struct group *ginfo = getgrgid (gid);
	if (ginfo != NULL)
		snprintf (name, MAXNAME, "%s", ginfo->gr_name);
	else
		snprintf (name, MAXNAME, "%d?", (int) gid);
	return name;
}
