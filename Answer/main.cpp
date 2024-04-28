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

inline int PowInt(int _base, int _exponent)
{
    int ret{ 1 };

    while (_exponent--)
    {
        ret *= _base;
    }

    return ret;
}

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;
    
    std::string notationNumber{};
    int base{};
    std::cin >> notationNumber >> base;

    int decimal{};

    //가장 낮은 자릿수부터 시작
    for (size_t i = 1; i <= notationNumber.size(); ++i)
    {
        char digit = notationNumber[notationNumber.size() - i];
        if (digit >= 'A')
        {
            digit -= 'A';
            digit += 10;
        }
        else
        {
            digit -= '0';
        }

        //현재 자리 숫자 * 자릿수 지수
        decimal += (int)digit * PowInt(base, (int)i - 1);
    }

    std::cout << decimal;
    return 0;
}
