#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main()
{
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("pid is %d, pointer address is %p\n",
            getpid(), p);
    *p = 0;
    while (1) {
        Spin(1);
        *p = *p + 1;
        printf("pid is %d, pointer address is %d\n",
                getpid(), *p);
    }
    return 0;
}
