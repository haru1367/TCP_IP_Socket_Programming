#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;  
	int snd_buf, rcv_buf, state;
	socklen_t len;
	
	// 소켓 생성
	sock = socket(PF_INET, SOCK_STREAM, 0);	
	
	// Output buffer size (송신 버퍼 크기) 조회
	len = sizeof(snd_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
	if (state)
		error_handling("getsockopt() error");
	
	// Input buffer size (수신 버퍼 크기) 조회
	len = sizeof(rcv_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len);
	if (state)
		error_handling("getsockopt() error");
	
	printf("Input buffer size: %d\n", rcv_buf);
	printf("Output buffer size: %d\n", snd_buf);
	return 0;
}

// 에러 핸들링 함수
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
