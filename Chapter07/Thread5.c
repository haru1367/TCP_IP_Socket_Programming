#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

void* thread_main1(void *arg);
void* thread_main2(void *arg);
void* thread_main3(void *arg);

// 세 개의 세마포어를 선언
static sem_t sem_one;
static sem_t sem_two;
static sem_t sem_thr;

int main(int argc, char *argv[]) 
{
	pthread_t t1_id, t2_id, t3_id;
	int thread_param = 5;

    // 세마포어 초기화
    sem_init(&sem_one, 0, 0);  // 초기 값 0
	sem_init(&sem_two, 0, 0);  // 초기 값 0
    sem_init(&sem_thr, 0, 1);  // 초기 값 1

	pthread_create(&t1_id, NULL, thread_main1, (void*)&thread_param);
    pthread_create(&t2_id, NULL, thread_main2, (void*)&thread_param);
    pthread_create(&t3_id, NULL, thread_main3, (void*)&thread_param);

	pthread_join(t1_id, NULL);
    pthread_join(t2_id, NULL);
    pthread_join(t3_id, NULL);

    // 세마포어 해제
    sem_destroy(&sem_one);
	sem_destroy(&sem_two);
    sem_destroy(&sem_thr);

	sleep(1);
  	puts("end of main");
	return 0;
}

void* thread_main1(void *arg) 
{
	int i;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; i++)
	{
        sleep(1);  
        sem_wait(&sem_one);  // sem_one 세마포어 대기
		puts("running thread1");
        sem_post(&sem_thr);  // sem_thr 세마포어 해제
	}
	return NULL;
}

void* thread_main2(void *arg) 
{
	int i;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; i++)
	{
        sleep(1);  
        sem_wait(&sem_two);  // sem_two 세마포어 대기
		puts("running thread2");	
        sem_post(&sem_one);  // sem_one 세마포어 해제
	}
	return NULL;
}

void* thread_main3(void *arg) 
{
	int i;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; i++)
	{
        sleep(1);  
        sem_wait(&sem_thr);  // sem_thr 세마포어 대기
		puts("running thread3");
        sem_post(&sem_two);  // sem_two 세마포어 해제
	}
	return NULL;
}
