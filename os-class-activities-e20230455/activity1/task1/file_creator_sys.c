#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    const char *text = "Hello from Operating Systems class!\n";

    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    ssize_t bytesWritten = write(fd, text, 36);
    if (bytesWritten < 0) {
        perror("Error writing file");
        close(fd);
        return 1;
    }

    if (close(fd) < 0) {
        perror("Error closing file");
        return 1;
    }

    const char *message = "File created successfully!\n";
    write(STDOUT_FILENO, message, 27);

    return 0;
}
