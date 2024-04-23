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

    int H, M;
    (void)scanf("%d %d", &H, &M);

    int minuteDayTime = (H * 60 + M) - 45;
    if (minuteDayTime < 0)
    {
        minuteDayTime += 60 * 24;
    }
    (void)printf("%d %d", minuteDayTime / 60, minuteDayTime % 60);

    return 0;
}
