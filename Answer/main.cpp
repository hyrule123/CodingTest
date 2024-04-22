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
    (void)printf("%.9lf", (double)a / (double)b);


    return 0;
}
