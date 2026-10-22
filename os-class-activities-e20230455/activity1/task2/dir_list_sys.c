
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;
    char output[512];

    int len = snprintf(output, sizeof(output),
                       "%-30s %10s\n",
                       "Filename", "Size (bytes)");
    write(STDOUT_FILENO, output, len);

    len = snprintf(output, sizeof(output),
                   "%-30s %10s\n",
                   "------------------------------", "----------");
    write(STDOUT_FILENO, output, len);

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            len = snprintf(output, sizeof(output),
                           "%-30s %10lld\n",
                           entry->d_name, (long long)fileStat.st_size);
            write(STDOUT_FILENO, output, len);
        }
    }

    closedir(dir);
    return 0;
}
