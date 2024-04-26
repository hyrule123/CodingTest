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

#include <string>
#include <array>


int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    int N{};
    std::cin >> N;

    
    int groupWordCount{ 0 };
    for (int i = 0; i < N; ++i)
    {
        bool groupFound[26]{};
        char word[101]{};
        std::cin >> word;
        size_t slen = strlen(word);
        
        bool isGroupWord{ true };
        for (size_t j = 0; j < slen; ++j)
        {
            //다른 알파벳이 나올때까지 진행
            if (word[j] != word[j + 1])
            {
                char alphabet2Idx = word[j] - 'a';

                //이미 찾은 그룹일경우 false
                if (groupFound[alphabet2Idx])
                {
                    isGroupWord = false;
                    break;
                }
                
                groupFound[alphabet2Idx] = true;
            }
        }

        if (isGroupWord)
        {
            ++groupWordCount;
        }
    }
    std::cout << groupWordCount;

    return 0;
}
