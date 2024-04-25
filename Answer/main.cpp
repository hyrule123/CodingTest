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

    unsigned int T;
    (void)scanf("%d", &T);

    for (unsigned int i = 0u; i < T; ++i)
    {
        int A, B;
        (void)scanf("%d %d", &A, &B);
        (void)printf("%d", A + B);

        if (i < (T - 1))
        {
            (void)printf("\n");
        }
    }

    return 0;
}
