#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define SIZE 4096

int main() {
    const char *name = "OS-mengseang";

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    void *ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sprintf(ptr, "Hello, ");
    sprintf(ptr + strlen("Hello, "), "this is shared memory IPC!");

    printf("Producer: wrote message to shared memory.\n");

    return 0;
}
