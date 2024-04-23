#ifndef LOCAL
#define USING_IOSTREAM (void)0
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#include <stdio.h>
#include <string.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    int A, B;
    (void)scanf("%d %d", &A, &B);

    constexpr const char* answers[] = { ">", "<", "==" };
    unsigned int index;

    if (A > B)
    {
        index = 0;
    }
    else if (A < B)
    {
        index = 1;
    }
    else
    {
        index = 2;
    }

    (void)printf("%s", answers[index]);

    return 0;
}
