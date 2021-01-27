#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/syscall.h> 

#define NUM_THREADS 10

char *getCurrentTime()
{
    time_t rawtime = time(NULL);
    struct tm *info = localtime(&rawtime);
    char *ret = (char*)malloc(80 * sizeof(char));
    strftime(ret, 80,"%m %d %H:%M:%S", info);
    return ret;
}

void *worker(void *args)
{
    int idx = *(int*)args;
    int sleep_time = 1 + rand()%NUM_THREADS;
    pid_t tid = syscall(SYS_gettid);
    printf("%s: thread %d id %d start\n", getCurrentTime(), idx, tid);
    printf("%s: thread %d id %d sleep %d sec\n", getCurrentTime(), idx, sleep_time, tid);
    sleep(sleep_time);
    printf("%s: thread %d id %d end\n", getCurrentTime(), idx, tid);

}

int main()
{
    srand(time(NULL));
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int result_code;
    pid_t pid = getpid();
    printf("main proc pid is %d\n", pid);
    sleep(10);
    // create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        result_code = pthread_create(&threads[i], NULL, worker, &thread_args[i]);
        assert(!result_code);
    }
    // wait all threads complete one by one
    for (int i = 0; i < NUM_THREADS; ++i) {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        printf("%s: main func: threads %d has ended\n", getCurrentTime(),i);
    }
    return 0;
}