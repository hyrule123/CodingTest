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
    
    char found[26]{};
    memset(found, -1, 26);

    std::cin >> S;
    
    for (int i = 0; i < 101; ++i)
    {
        if ('\0' == S[i])
        {
            break;
        }
        
        //ASCII 97 == 'a'
        int pos = S[i] - 97;
        if (-1 == found[pos])
        {
            found[pos] = i;
        }
    }

    for (int i = 0; i < 26; ++i)
    {
        std::cout << (int)(found[i]) << ' ';
    }
    
    return 0;
}
