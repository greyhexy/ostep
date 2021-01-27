#include <stdio.h>
#include <stdlib.h>
#include "common.h"

volatile int counter;
int loops;

void *worker(void *arg)
{
    int i;
    for (i = 0; i < loops; ++i)
        counter++;
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "please input the number of threads!");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("initial counter value is %d\n", counter);

    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("final counter value is %d\n", counter);
    return 0;
}
