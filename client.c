#include <stdio.h>          // printf, fprintf, perror
#include <stdlib.h>         // exit
#include <string.h>         // memset
#include <unistd.h>         // close
#include <sys/types.h>      // socket types
#include <sys/socket.h>     // socket, connect, recv
#include <netinet/in.h>     // sockaddr_in
#include <arpa/inet.h>      // htons, inet_ntoa
#include <netdb.h>          // gethostbyname, struct hostent
#include <sys/select.h>
#include <signal.h>

#define MAXDATASIZE 1000
void chatting(int sd){
    char buf[MAXDATASIZE];

    fd_set rfedet, rfedet_copy;
    FD_ZERO(&rfedet);
    FD_SET(0, &rfedet);
    FD_SET(sd, &rfedet);

    while(1){
        rfedet_copy =  rfedet;
        select(sd + 1, &rfedet_copy, NULL, NULL, NULL); // 이벤트가 발생!
        if(FD_ISSET(0, &rfedet_copy)){
            fgets(buf, sizeof(buf), stdin);
            send(sd, buf, strlen(buf), 0);
        }
        else if(FD_ISSET(sd, &rfedet_copy)){
            int numbytes = recv(sd, buf, MAXDATASIZE - 1, 0);
            buf[numbytes] = '\0';
            printf("%s", buf);
        }
    }
}
int sockfd, numbytes;
socklen_t addr_len;
char buf[MAXDATASIZE];
struct hostent *he;
struct sockaddr_in server_addr;
void signal_handler(int signum) {
    if (signum == SIGINT) {
        close(sockfd);
        printf("\nSIGINT 감지. 프로그램 종료.\n");
        exit(0); 
    }
}
void signal_set() {
    // SIG_INT일때 핸들러 처리 
    struct sigaction sa_int;    
    sa_int.sa_handler = signal_handler;  
    sigemptyset(&sa_int.sa_mask);        
    sa_int.sa_flags = 0;                 
    sigaction(SIGINT, &sa_int, NULL);    

    // SIG_INT가 아니면 전부 무시
    for (int i = 1; i <= 31; i++) {
        if (i == SIGINT) continue; 
        signal(i, SIG_IGN);   
    }
}
int main(int argc, char *argv[])
{
    signal_set();

    if (argc != 2) {
        fprintf(stderr, "usage : client hostname\n");
        exit(1);
    }
    
    if ((he = gethostbyname(argv[1])) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(60000);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(server_addr.sin_zero), '\0', 8);
    printf("접속한 서버 [ %s ]\n", inet_ntoa(server_addr.sin_addr));
    
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    chatting(sockfd);

    close(sockfd);
    return 0;
}
