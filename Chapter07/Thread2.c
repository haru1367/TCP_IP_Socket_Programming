#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* thread_main(void *arg);

int main(int argc, char *argv[]) 
{
	pthread_t t_id;
	int thread_param = 5;
	void *thr_ret;  // 쓰레드의 반환 값을 저장하기 위한 포인터

	// 쓰레드 생성
	if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)
	{
		puts("pthread_create() error");
		return -1;
	}

	// 쓰레드가 종료될 때까지 대기하고 반환 값을 받음
	if (pthread_join(t_id, &thr_ret) != 0)
	{
		puts("pthread_join() error");
		return -1;
	}

	// 쓰레드의 반환 값을 출력
	printf("Thread return message: %s\n", (char*)thr_ret);
	free(thr_ret);  // 동적으로 할당한 메모리를 해제
	return 0;
}

void* thread_main(void *arg) 
{
	int i;
	int cnt = *((int*)arg);
	char *msg = (char*)malloc(sizeof(char) * 50);
	strcpy(msg, "Hello, I'm thread~\n");  // 메시지를 할당하고 복사

	for (i = 0; i < cnt; i++)
	{
		sleep(1);
		puts("running thread");
	}

	// 쓰레드의 반환 값으로 메시지를 반환 (메인 쓰레드에서 해제해야 함)
	return (void*)msg;
}
