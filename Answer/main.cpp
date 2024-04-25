#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    unsigned int T;
    (void)scanf("%u", &T);

    unsigned int A, B;
    for (unsigned int i = 0u; i < T; ++i)
    {
        (void)scanf("%u %u", &A, &B);
        (void)printf("%u\n", A + B);
    }

    return 0;
}
