#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "common.h"

int main() {
    mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY);

    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    struct mq_attr attr;
    mq_getattr(mq, &attr);

    char buffer[MAX_SIZE + 1];

    ssize_t bytes_read = mq_receive(mq, buffer, attr.mq_msgsize, NULL);

    if (bytes_read == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Receiver: received message: %s\n", buffer);

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    printf("Receiver: message queue unlinked.\n");

    return 0;
}
