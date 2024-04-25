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

    unsigned int N;
    (void)scanf("%d", &N);
    
    for (int i = 0; i < 9; ++i)
    {
        (void)printf("%d * %d = %d", N, i + 1, N * (i + 1));

        if (i < 8)
        {
            (void)printf("\n");
        }
    }

    return 0;
}
