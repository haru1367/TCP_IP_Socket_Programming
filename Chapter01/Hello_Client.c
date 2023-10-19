#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock; // 소켓 디스크립터를 저장할 변수
	struct sockaddr_in serv_addr; // 서버의 주소 정보를 저장할 구조체
	char message[30]; // 서버로부터 받을 메시지를 저장할 버퍼
	int str_len; // 읽은 메시지의 길이를 저장할 변수
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]); // 프로그램 사용법 출력
		exit(1); // 프로그램 종료
	}
	
	sock = socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성
	if(sock == -1)
		error_handling("socket() error"); // 소켓 생성 실패 시 오류 처리 함수 호출
	
	memset(&serv_addr, 0, sizeof(serv_addr)); // serv_addr 구조체 초기화
	serv_addr.sin_family = AF_INET; // 주소 체계 설정 (IPv4)
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 서버 IP 주소 설정
	serv_addr.sin_port = htons(atoi(argv[2])); // 서버 포트 번호 설정
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
		error_handling("connect() error!"); // 서버에 연결 실패 시 오류 처리 함수 호출
	
	str_len = read(sock, message, sizeof(message) - 1); // 서버로부터 데이터 읽기
	if(str_len == -1)
		error_handling("read() error!"); // 데이터 읽기 실패 시 오류 처리 함수 호출
	
	message[str_len] = '\0'; // 문자열 마지막에 널 문자 추가하여 문자열 종료
	printf("Message from server: %s \n", message); // 서버로부터 받은 메시지 출력  
	close(sock); // 소켓 닫기
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr); // 오류 메시지를 표준 오류 스트림에 출력
	fputc('\n', stderr); // 개행 문자 출력
	exit(1); // 프로그램 종료
}
