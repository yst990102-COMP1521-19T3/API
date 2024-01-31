#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void file_mode(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        file_mode(argv[arg]);
    }
    return 0;
}

// convert octal mode to -rwxrwxrwx string and print itm

void file_mode(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    mode_t mode = s.st_mode;

    char permissions[] = "?rwxrwxrwx";
    int n_permissions = strlen(permissions);

    if (S_ISREG(mode)) {
        permissions[0] = '-';
    } else if (S_ISDIR(mode)) {
        permissions[0] = 'd';
    }

    for (int i = 1; i < n_permissions; i++) {
        if (!(mode & (1 << (i - 1)))) {
            permissions[n_permissions - i] = '-';
        }
    }

    printf("%s %s\n", permissions, pathname);
}
