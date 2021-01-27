#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        printf("this is child!, %d\n", getpid());
    }
    printf("my pid is %d\n", getpid());
    return 0;
}
