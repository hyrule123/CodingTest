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

    unsigned int n;
    (void)scanf("%d", &n);

    unsigned int sum{ 0u };
    for (unsigned int i = 1u; i <= n; ++i)
    {
        sum += i;
    }
    (void)printf("%d", sum);

    return 0;
}
