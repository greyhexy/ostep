#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "please input a string!");
        exit(1);
    }
    const char *s = argv[1];
    while (1) {
        Spin(1);
        printf("%s\n", s);
    }
    return 0;
}
