#ifndef LOCAL
#define USING_IOSTREAM (void)0
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

int sLen;

#include <stdio.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    int buddaYear;

    (void)scanf("%d", &buddaYear);
    (void)printf("%d", buddaYear - 544 + 1);

    return 0;
}
