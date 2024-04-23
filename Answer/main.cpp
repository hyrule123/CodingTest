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

    int x, y;
    (void)scanf("%d\n%d", &x, &y);

    //x != 0, y != 0
    int quadrant;
    if (x > 0)
    {
        if (y > 0)
        {
            quadrant = 1;
        }
        else
        {
            quadrant = 4;
        }
    }
    else
    {
        if (y > 0)
        {
            quadrant = 2;
        }
        else
        {
            quadrant = 3;
        }
    }

    (void)printf("%d", quadrant);

    return 0;
}
