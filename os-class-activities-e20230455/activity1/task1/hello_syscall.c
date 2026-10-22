#include <unistd.h>

int main(void) {
    const char *message = "\nHello, System Call!\n";
    write(1, message, 19);
    return 0;
}