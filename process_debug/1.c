#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <ctype.h>
#include <pthread.h> 
#include<semaphore.h>
#define MAX_THREAD 3 /* 线程的个数 */

unsigned long long main_counter, counter[MAX_THREAD]; 
/* unsigned long  long是比long还长的整数 */
sem_t S1,S2;

void* thread_worker(void*); 

void *thread_worker(void *p){
    int thread_num;
    thread_num=(int)p;
    for(;;){
        sem_wait(&S1);
        sem_wait(&S2);
        counter[thread_num]++;/* 本线程的counter加一 */
        main_counter++;/* 主counter 加一 */
        sem_post(&S2);
        sem_post(&S1);
   }
}

int main(int argc,char *argv[]) { 
    int i,rtn,ch;
    pthread_t pthread_id[MAX_THREAD]={0};
    sem_init(&S1,0,1);
    sem_init(&S2,0,1);
   for(i=0;i<MAX_THREAD;i++){
        rtn=pthread_create(&pthread_id[i],NULL,thread_worker,(void*)i);
   }
   do
   {
        unsigned long long sum=0;
        sem_wait(&S1);
        sem_wait(&S2);  
        for(i=0;i<MAX_THREAD;i++){/* 求所有counter的和 */
            sum+=counter[i];
            printf("第%d个counter的值是%llu\n",i+1,counter[i]);
        }

    printf("main_counter的值:%llu sum的值%llu\n",main_counter,sum);
    sem_post(&S2);
    sem_post(&S1);
    }while((ch=getchar())!='q');
    return 0;
}
