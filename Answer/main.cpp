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

    unsigned int d1, d2, d3;
    (void)scanf("%d %d %d", &d1, &d2, &d3);

    unsigned int money;
    if (d1 == d2 && d2 == d3)
    {
        money = 10000 + d1 * 1000;
    }
    else if (d1 == d2 || d1 == d3)
    {
        money = 1000 + d1 * 100;
    }
    else if (d2 == d3)
    {
        money = 1000 + d2 * 100;
    }
    else
    {
        money = d1 > d2 ? d1 : d2;
        money = money > d3 ? money : d3;
        money *= 100;
    }
    (void)printf("%u", money);

    return 0;
}
