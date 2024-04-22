#ifndef LOCAL
#define PAUSE (void)0
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //LOCAL


#include <stdio.h>
int main()
{
    READ_INPUT;
    WRITE_OUTPUT;

    int a, b;
    
    scanf("%d %d", &a, &b);
    printf("%d", a + b);

    PAUSE;
    return 0;
}
