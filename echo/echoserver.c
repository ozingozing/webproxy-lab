#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv)
{
    //어...소켓...만들어야 하는데...?
    //어케함?
    //1.일단...서버에 리스닝 소켓은 있어야지 밥이됐든 죽이 됐든
    //  뭘 하겠는데...그리고...?열결에 성공하면 그에 파생된
    //  소켓으로 연결해줘야 하는데...
    //2.그리고...클라이언트에서 연결을 시도를 여쪽 host IP,Port로
    //  접속 시도하겠지...?
    //3.그럼 서버도 그걸 받아야 하는데...client주소 어케알지...?
    //  아 그거 addrinfo 구조체에 클라정보 있던데...그걸 OS단에서
    //  accept함수 호출할 때 클라이언트 IP랑 Port다 저장해줌...
    
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    struct sockaddr_in cliaddr;
    if(argc != 2)   
        exit(0);

    listenfd = Open_listenfd(argv[1]);

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        printf("Client IP: %s\n", inet_ntoa(cliaddr.sin_addr));
        printf("Client port: %d\n", ntohs(cliaddr.sin_port));
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}



// void echo(int connfd);

// int main(int argc, char **argv)
// {
//     int listenfd, connfd;
//     socklen_t clientlen;
//     struct sockaddr_storage clientaddr;
//     char client_hostname[MAXLINE], client_port[MAXLINE];

//     if (argc != 2)
//     {
//         fprintf(stderr, "usage : %s <prot>\n", argv[0]);
//         exit(0);
//     }
//     listenfd = Open_listenfd(argv[1]);
//     while (1)
//     {
//         clientlen = sizeof(struct sockaddr_storage);
//         connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
//         Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
//         printf("Connected to (%s, %s)\n", client_hostname, client_port);
//         echo(connfd);
//         Close(connfd);
//     }
//     exit(0);
// }

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %d bytes\n", (int)n);
        Fputs(buf, stdout);
        Rio_writen(connfd, buf, n);
    }
}