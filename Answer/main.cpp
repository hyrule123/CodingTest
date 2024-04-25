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

    unsigned int X, N;
    (void)scanf("%u\n%u", &X, &N);

    unsigned int sum{ 0u };
    for (unsigned int i = 0u; i < N; ++i)
    {
        unsigned int a, b;
        (void)scanf("%u %u", &a, &b);
        sum += a * b;
    }

    if (X == sum)
    {
        (void)printf("Yes");
    }
    else
    {
        (void)printf("No");
    }

    return 0;
}
