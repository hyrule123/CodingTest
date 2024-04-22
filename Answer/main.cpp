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

    constexpr const char* cat =
        R"(\    /\
 )  ( ')
(  /  )
 \(__)|)";

    (void)printf("%s", cat);

    return 0;
}
