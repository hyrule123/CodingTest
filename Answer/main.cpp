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

    int H, M, D;
    (void)scanf("%d %d\n%d", &H, &M, &D);

    constexpr int dayInMinute = 24 * 60;

    int endTime = H * 60 + M + D;
    if (endTime >= dayInMinute)
    {
        endTime -= dayInMinute;
    }

    (void)printf("%d %d", endTime / 60, endTime % 60);

    return 0;
}
