#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

void error_handling(char* message);

int main(void)
{
	int fd;                   // 파일 디스크립터를 저장할 변수
	char buf[BUF_SIZE];       // 데이터를 읽고 쓸 버퍼

	fd = open("data.txt", O_RDWR);  // "data.txt" 파일을 열고 파일 디스크립터를 반환
	if (fd == -1)
		error_handling("open() error!");  // 파일 열기 실패 시 오류 처리 함수 호출

	printf("file descriptor: %d\n", fd);  // 파일 디스크립터 출력

	// 표준 입력(0)에서 데이터를 읽어서 buf에 저장
	if (read(0, buf, sizeof(buf)) == -1)
		error_handling("read() error!");  // 읽기 실패 시 오류 처리 함수 호출

	// 파일 디스크립터(fd)를 통해 buf의 내용을 파일에 씀
	if (write(fd, buf, sizeof(buf)) == -1) {
		error_handling("write() error!");  // 쓰기 실패 시 오류 처리 함수 호출
	}

	printf("file data: %s", buf);  // 버퍼에 저장된 데이터 출력

	close(fd);  // 파일 디스크립터를 닫음
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);  // 오류 메시지를 표준 오류 스트림에 출력
	fputc('\n', stderr);     // 개행 문자 출력
	exit(1);                 // 프로그램 종료
}
