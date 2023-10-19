#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_main(void *arg);

int main(int argc, char *argv[]) 
{
	pthread_t t_id;            // 쓰레드 식별자
	int thread_param = 5;      // 쓰레드에 전달할 인자

	if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)
	{
		puts("pthread_create() error");
		return -1;
	}

	// 메인 쓰레드가 10초 동안 대기
	sleep(10);
	puts("end of main");
	return 0;
}

void* thread_main(void *arg) 
{
	int i;
	int cnt = *((int*)arg);   // 쓰레드에 전달된 인자를 정수로 변환

	// 주어진 횟수만큼 반복하면서 "running thread"를 출력하고 1초 대기
	for (i = 0; i < cnt; i++)
	{
		sleep(1);
		puts("running thread");
	}

	return NULL;
}
