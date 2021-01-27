#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define N 10

void *mythread(void *arg) {
  pid_t pid = syscall(__NR_gettid);
  printf("thread id %d, msg %s\n", pid, (char *)arg);
  return NULL;
}

int main(int argc, char *argv[]) {
  printf("main thread: begin\n");
  char msgs[N][2];
  for (int i = 0; i < N; ++i) {
      msgs[i][0] = 'a' + i;
      msgs[i][1] = '\0';
  }
  pthread_t pool[N];
  for (int i = 0; i < N; ++i) {
    // char msg[2] = {'a' + i, '\0'};
    int err = pthread_create(pool + i, NULL, mythread, msgs[i]);
    printf("msg is %s, err is %d\n", msgs[i], err);
  }
  printf("start to join :\n");
  for (int i = 0; i < N; ++i)
    pthread_join(pool[i], NULL);
  printf("main thread: end\n");
  return 0;
}
