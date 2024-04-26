#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
#include <limits>

#include <vector>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    char S[101]{};
    std::cin >> S;
    int slen = (int)strlen(S);
    int loopCount = slen / 2;
    --slen;
    
    bool isPalindrome = true;
    for (int i = 0; i < loopCount; ++i)
    {
        if (S[i] != S[slen - i])
        {
            isPalindrome = false;
        }
    }
    std::cout << (isPalindrome ? 1 : 0);

    return 0;
}
