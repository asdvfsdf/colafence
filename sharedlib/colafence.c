#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <dlfcn.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

#define INTERVAL 500000

#define DEFENCE 256
#define PAGE_SIZE 4096

int fence_enable;

const char* analysis_dir;
const char* output_file;
FILE* file = NULL; 

extern void *__libc_malloc(size_t size);

void __attribute__((constructor)) timer_init(void) {
    
    printf("good\n");
    analysis_dir = getenv("ANALYSIS");
    init_timer();
    init_fence_output();
}

int malloc_hook_active = 0;

struct sigaction sa;
struct itimerval timer;

unsigned long *pool;

void hook_enable(){
    malloc_hook_active = 1;

    timer.it_value.tv_sec = 0;    // 0秒后触发
    timer.it_value.tv_usec = INTERVAL; // 500毫秒
    timer.it_interval.tv_sec = 0;  // 间隔时间为0，表示不重复定时
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

void init_timer(){
    // 注册定时器信号处理函数
    sa.sa_handler = hook_enable;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    // 设置定时器
    timer.it_value.tv_sec = 0; // 5秒后触发
    timer.it_value.tv_usec = INTERVAL;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // 激活定时器
    setitimer(ITIMER_REAL, &timer, NULL);

}

int init_fence_output(){  

    if(access(analysis_dir, F_OK) == 0){

    }else{

        int result = mkdir(analysis_dir, 0777);

        if (result == 0) {
            printf("dir init success\n");
        } else {
            printf("dir init failed\n");
            perror("Error ");
            exit(EXIT_FAILURE);
        }

    }

    char pid[10];
    sprintf(pid, "%d", (int)getpid());

    FILE *file;
    file = fopen(strcat(strcat(analysis_dir, "/"), pid), "w+");

    if (file != NULL) {
        fprintf(file, "colafence output\n");
        fclose(file);
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}

int init_pool(){

    pool = (unsigned long *)malloc(PAGE_SIZE * DEFENCE);
    
    if(!pool){
      exit(EXIT_FAILURE);
    }
}



void* my_malloc_hook (size_t size, void *caller)
{
  void *result;

  // deactivate hooks for logging
  malloc_hook_active = 0;

  result = malloc(size);
  printf("it works!");
  // reactivate hooks
  malloc_hook_active = 0;

  return result;
}

void* malloc (size_t size)
{
  void *caller = __builtin_return_address(0);

  if (malloc_hook_active)
    return my_malloc_hook(size, caller);

  return __libc_malloc(size);
}