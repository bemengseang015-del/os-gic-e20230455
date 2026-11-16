#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE 4096

int main() {
    const char *name = "OS-mengseang";

    int shm_fd = shm_open(name, O_RDONLY, 0666);

    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Consumer: read message: %s\n", (char *)ptr);

    shm_unlink(name);
    printf("Consumer: shared memory unlinked.\n");

    return 0;
}
