#ifndef LOCAL
#define USING_IOSTREAM (void)0
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

int sLen;

#include <stdio.h>
#include <string.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    char str[50 + 3];

    (void)scanf("%s", &str);

    (void)strcat(str, "??!");

    (void)printf("%s", str);

    return 0;
}
