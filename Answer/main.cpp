#ifndef LOCAL
#define USING_IOSTREAM (void)0
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#include <stdio.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    unsigned long N;
    (void)scanf("%d", &N);

    N /= 4u;

    for (unsigned long i = 0u; i < N; ++i)
    {
        (void)printf("long ");
    }
    (void)printf("int");
    

    return 0;
}
