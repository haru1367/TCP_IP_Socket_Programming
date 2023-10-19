#include <stdio.h>
#include <pthread.h>

// 전역 변수로 합을 저장할 변수 선언
int sum = 0;

// 쓰레드 함수 원형 선언
void* thread_summation(void* arg);

int main(int argc, char* argv[])
{
    pthread_t id_t1, id_t2;
    int range1[] = {1, 5};
    int range2[] = {6, 10};
    
    // 첫 번째 쓰레드 생성 및 실행
    pthread_create(&id_t1, NULL, thread_summation, (void*)range1);
    
    // 두 번째 쓰레드 생성 및 실행
    pthread_create(&id_t2, NULL, thread_summation, (void*)range2);

    // 두 쓰레드의 실행이 완료될 때까지 대기
    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);

    // 결과 출력
    printf("result: %d\n", sum);

    return 0;
}

// 쓰레드 함수 정의
void* thread_summation(void* arg) 
{
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];

    while (start <= end)
    {
        sum += start;
        start++;
    }

    return NULL;
}
