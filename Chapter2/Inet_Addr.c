#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *addr1 = "127.212.124.78";  // 첫 번째 IP 주소를 문자열로 설정
	char *addr2 = "127.212.124.256"; // 두 번째 IP 주소를 문자열로 설정

	unsigned long conv_addr = inet_addr(addr1); // 첫 번째 주소를 네트워크 바이트 순서로 변환하여 변수에 저장
	if (conv_addr == INADDR_NONE)
		printf("Error occured! \n"); // 변환 실패 시 오류 메시지 출력
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr); // 변환된 네트워크 바이트 순서의 정수값 출력
	
	conv_addr = inet_addr(addr2); // 두 번째 주소를 네트워크 바이트 순서로 변환하여 변수에 저장
	if (conv_addr == INADDR_NONE)
		printf("Error occureded \n"); // 변환 실패 시 오류 메시지 출력
	else
		printf("Network ordered integer addr: %#lx \n\n", conv_addr); // 변환된 네트워크 바이트 순서의 정수값 출력
	
	return 0;
}
