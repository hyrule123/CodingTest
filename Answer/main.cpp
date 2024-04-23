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

    int score;
    (void)scanf("%d", &score);

    constexpr const char* answers[] = { "F", "D", "C", "B", "A" };

    if (score < 50)
    {
        score = 50;
    }
    else if (score == 100)
    {
        score = 99;
    }

    score = (score - 50) / 10;

    (void)printf("%s", answers[score]);

    return 0;
}
