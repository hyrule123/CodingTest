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

    using uint64 = unsigned long long;

    uint64 A, B, C;

    (void)scanf("%llu %llu %llu", &A, &B, &C);
    (void)printf("%llu", A + B + C);

    return 0;
}
