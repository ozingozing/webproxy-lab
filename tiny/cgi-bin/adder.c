/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "../csapp.h"

int main(void)
{
  char *buf, *p, *method;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  int n1 = 0, n2 = 0;

  /* Extract the two arguments */
  /* 두 개의 인자 추출 */
  /*getenv("QUERY_STRING") 함수를 사용하여 환경 변수 QUERY_STRING에서 쿼리 스트링을 추출합니다.
  이 쿼리 스트링은 URL의 ? 다음에 오는 부분으로, 예를 들어 num1=3&num2=4 와 같은 형태입니다.*/
  if ((buf = getenv("QUERY_STRING")) != NULL)
  {
    // strchr 함수를 사용하여 & 문자를 찾고, 이 위치를 NULL 문자로 대체하여 문자열을 두 부분으로 분리합니다.
    p = strchr(buf, '&');
    *p = '\0';
    strcpy(arg1, buf);
    strcpy(arg2, p + 1);
    n1 = atoi(arg1); // 첫 번째 인자를 정수로 변환
    n2 = atoi(arg2); // 두 번째 인자를 정수로 변환
    /* Homework: 11.10 */
    // sscanf 함수를 사용하여 분리된 각 부분에서 숫자를 추출하고, n1과 n2에 저장합니다.
    sscanf(buf, "num1=%d", &n1);
    sscanf(p + 1, "num2=%d", &n2);
  }

  /* Make the response body */
  /* 응답 본문 생성 */
  /*
  응답 본문 생성:
  sprintf 함수를 여러 번 호출하여 content 배열에 HTML 형식의 응답 본문을 구성합니다. 이 과정에서 두 숫자의 합 결과도 포함됩니다.
  덧셈 결과를 포함한 각종 정보를 HTML 포맷으로 content 문자열에 추가하며, 최종적으로 방문에 대한 감사 메시지를 추가합니다.
  */
  sprintf(content, "QUERY_STRING=%s", buf);
  sprintf(content, "Welcome to add.com: ");
  sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
  sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
          content, n1, n2, n1 + n2);
  sprintf(content, "%sThanks for visiting!\r\n", content);

  /* Generate the HTTP response */
  /* HTTP 응답 생성 */
  /*
  HTTP 응답 헤더 및 본문 출력:
  printf 함수를 사용하여 HTTP 응답 헤더를 출력합니다. 이 헤더에는 Connection: close, Content-length,
  그리고 Content-type: text/html 등이 포함됩니다. Content-length는 content 문자열의 길이를 기반으로 계산됩니다.
  HTTP 헤더 다음에 printf를 사용하여 HTML로 구성된 응답 본문(content)을 출력합니다.
  */
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content); // 생성된 응답 본문 출력
  /*
  출력 버퍼 비우기 및 프로그램 종료:
  fflush(stdout);를 호출하여 표준 출력 버퍼를 비워, 데이터가 클라이언트에 즉시 전송되도록 합니다.
  exit(0);을 호출하여 프로그램을 종료합니다.
  */
  fflush(stdout); // 출력 버퍼를 비워줌
  exit(0);
}
/* $end adder */