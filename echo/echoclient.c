#include "csapp.h"

int main(int argc, char **argv)
{
    //여기선 진짜 OpenClientfd밖에 안함
    //진짜 접속 시도 말곤 아무것도 안함
    //만약 연결 됐다면 RIO사용 시작
    //저 RIO는 init으로 초기화하고
    //Fgets으로 buf에 저장한 데이터를
    //Rio_writen으로 buf에 저장한걸 clientfd에 덮어쓰기
    //하고 서버쪽을 던짐
    //Rio_readlineb로 서버쪽에서 던진 데이터를 buf에 읽어들임
    //Fputs로 출력

    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if(argc != 3)
        exit(0);

    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while(Fgets(buf, MAXLINE, stdin) != NULL)
    {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }
    Close(clientfd);
    exit(0);
}


// int main(int argc, char **argv)
// {
//     int clientfd;
//     char *host, *port, buf[MAXLINE];
//     rio_t rio;

//     if (argc != 3)
//     {
//         fprintf(stderr, "usage : %s <host> <prot>\n", argv[0]);
//         exit(0);
//     }

//     host = argv[1];
//     port = argv[2];

//     clientfd = Open_clientfd(host, port);
//     Rio_readinitb(&rio, clientfd);

//     while (Fgets(buf, MAXLINE, stdin) != NULL)
//     {
//         Rio_writen(clientfd, buf, strlen(buf));
//         Rio_readlineb(&rio, buf, MAXLINE);
//         Fputs(buf, stdout);
//     }
//     Close(clientfd);
//     exit(0);
//}