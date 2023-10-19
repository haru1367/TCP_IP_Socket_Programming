#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int i;
    struct hostent *host;

    // 명령행 인자 체크
    if (argc != 2) {
        printf("Usage : %s <addr>\n", argv[0]);
        exit(1);
    }
    
    // 호스트 정보 조회
    host = gethostbyname(argv[1]);
    if (!host)
        error_handling("gethost... error");

    printf("Official name: %s\n", host->h_name);
    
    // 별칭(alias) 목록 출력
    for (i = 0; host->h_aliases[i]; i++)
        printf("Aliases %d: %s\n", i + 1, host->h_aliases[i]);
    
    // 주소 타입 출력 (IPv4 또는 IPv6)
    printf("Address type: %s\n", 
        (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

    // IP 주소 목록 출력
    for (i = 0; host->h_addr_list[i]; i++)
        printf("IP addr %d: %s\n", i + 1,
            inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
