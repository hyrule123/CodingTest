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

    unsigned int year;
    (void)scanf("%u", &year);
    (void)printf("%d", (0 == year % 400) ? 1 : (0 != year % 100 && 0 == year % 4) ? 1 : 0);

    return 0;
}
