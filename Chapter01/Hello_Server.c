#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;          // 서버 소켓 디스크립터
	int clnt_sock;          // 클라이언트 소켓 디스크립터

	struct sockaddr_in serv_addr;  // 서버 주소 구조체
	struct sockaddr_in clnt_addr;  // 클라이언트 주소 구조체
	socklen_t clnt_addr_size;      // 클라이언트 주소 구조체의 크기

	char message[10];       // 메시지를 저장할 버퍼

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);  // 프로그램 사용법 출력
		exit(1); // 프로그램 종료
	}

	// 서버 소켓 생성
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	// 서버 주소 구조체 초기화
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; // IPv4 형식 설정
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 네트워크 인터페이스에서 접속 허용
	serv_addr.sin_port = htons(atoi(argv[1])); // 사용자가 입력한 포트 번호 설정

	// 소켓에 주소 정보 할당
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	// 연결 대기 상태로 변경
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);

	// 클라이언트의 연결 요청을 수락
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1)
		error_handling("accept() error");

	// 표준 입력에서 메시지를 읽어서 클라이언트에게 전송
	read(0, message, 10);
	write(clnt_sock, message, sizeof(message));

	char *str_ptr;
	printf("clnt addr:%#x \n", clnt_addr.sin_addr);  // 클라이언트 주소 출력
	printf("clnt port:%#x \n", clnt_addr.sin_port);  // 클라이언트 포트 출력
	str_ptr = inet_ntoa(clnt_addr.sin_addr);  // 클라이언트 주소를 문자열로 변환
	printf("Dotted_Decimal notation1: %s\n", str_ptr);

	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr); // 오류 메시지를 표준 오류 스트림에 출력
	fputc('\n', stderr);    // 개행 문자 출력
	exit(1);                // 프로그램 종료
}
