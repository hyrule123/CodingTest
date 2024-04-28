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

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    unsigned long long fromDecimal{};
    unsigned long long toBase{};
    std::cin >> fromDecimal >> toBase;

    //1. 최저 지수에서 시작해서 하나씩 올려가기(대신 답이 거꾸로 들어감) ->이걸로
    //2. 최대 지수까지 올린후 하나씩 내려오기
    std::string notation{};

    unsigned long long exp = 1;
    while (true)
    {
        if (exp > fromDecimal)
        {
            break;
        }


        unsigned long long prevExp = exp;
        exp *= toBase;

        char remainder = (char)((fromDecimal % exp) / prevExp);
        if (remainder >= 10)
        {
            remainder += ('A' - 10);
        }
        else
        {
            remainder += '0';
        }
        notation.push_back(remainder);
    }

    for (int i = (int)notation.size() - 1; i >= 0; --i)
    {
        std::cout << notation[i];
    }
    return 0;
}
