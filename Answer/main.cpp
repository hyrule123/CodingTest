#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL


#include <stdio.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    int a, b;

    (void)scanf("%d %d", &a, &b);

    //두 자연수 A와 B가 주어진다. 이때, A+B, A-B, A*B, A/B(몫), A%B(나머지)를 출력하는 프로그램을 작성하시오. 
    (void)printf("%d\n", a + b);
    (void)printf("%d\n", a - b);
    (void)printf("%d\n", a * b);
    (void)printf("%d\n", a / b);
    (void)printf("%d", a % b);


    return 0;
}
