#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char* message);

int main(void)
{
	int fd1,fd2;
	char buf[]="Let's go!\n";
	
	fd1=open("data.txt", O_CREAT /*필요시 파일 생성*/ |O_WRONLY/*쓰기용도*/ |O_TRUNC /*모든 내용 삭제*/); // fopen -> 파일을 열기위한 함수, open -> 파일,장치등을 열기위한 함수 
	if(fd1==-1)  // 파일을 열지 못했을 때
		error_handling("open() error!");
	printf("file descriptor: %d \n", fd1); // 파일 디스크립트 값 출력

	fd2=open("data2.txt", O_CREAT /*필요시 파일 생성*/ |O_WRONLY/*쓰기용도*/ |O_TRUNC /*모든 내용 삭제*/); // fopen -> 파일을 열기위한 함수, open -> 파일,장치등을 열기위한 함수 
	if(fd2==-1)  // 파일을 열지 못했을 때
		error_handling("open() error!");
	printf("file descriptor: %d \n", fd2); // 파일 디스크립트 값 출력

	if(write(fd1, buf, sizeof(buf))==-1)  //파일에 쓰기 실패했을 때
		error_handling("write() error!");

	close(fd1);
	if(write(fd2, buf, sizeof(buf))==-1)  //파일에 쓰기 실패했을 때
		error_handling("write() error!");

	close(fd2);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

/*
root@com:/home/swyoon/tcpip# gcc low_open.c -o lopen
root@com:/home/swyoon/tcpip# ./lopen
file descriptor: 3 
root@com:/home/swyoon/tcpip# cat data.txt
Let's go!
root@com:/home/swyoon/tcpip# 
*/
