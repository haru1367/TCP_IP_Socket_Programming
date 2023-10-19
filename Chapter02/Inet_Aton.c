#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

// 오류 처리 함수 정의
void error_handling(char *message);

int main(int argc, char *argv[])
{
	char *addr = "127.232.124.79"; // 변환할 IP 주소를 문자열로 설정
	struct sockaddr_in addr_inet; // IP 주소를 저장할 구조체

	// inet_aton 함수를 사용하여 문자열 형태의 IP 주소를 네트워크 바이트 순서로 변환하여 addr_inet 구조체에 저장
	if (!inet_aton(addr, &addr_inet.sin_addr))
		error_handling("Conversion error"); // 변환 실패 시 오류 메시지 출력 및 오류 처리 함수 호출
	else
		printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr); // 변환된 네트워크 바이트 순서의 정수값 출력
	return 0;
}

// 오류 처리 함수 구현
void error_handling(char *message)
{
	fputs(message, stderr); // 오류 메시지를 표준 오류 스트림에 출력
	fputc('\n', stderr);    // 개행 문자 출력
	exit(1);                // 프로그램 종료
}
