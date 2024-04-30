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

inline int PowInt(const int _base, int _exponent)
{
    int ret = 1;

    while (0 < _exponent--)
    {
        ret *= _base;
    }

    return ret;
}

inline int GetDigitCount(int _num)
{
    int digitCount{};

    while (0 != _num)
    {
        _num /= 10;
        ++digitCount;
    }

    return digitCount;
}


int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int num{};
    std::cin >> num;

    int digitSize = GetDigitCount(num);

    //각 자리당 최대 9까지 뺼 수 있으므로
    //최소값(시작값)은 9 * 자리갯수를 뺀 값이 될수밖에 없음.
    int start = num - 9 * digitSize;
    //예외처리
    if (start < 0)
    {
        start = 0;
    }

    //시작값부터 자신의 값 까지
    for (start; start < num; ++start)
    {
        int sum = start;
        int exp = PowInt(10, GetDigitCount(start) - 1);

        //자릿수별로 더해준다.
        int temp = start;
        while (0 != temp)
        {
            int div = temp / exp;
            temp -= div * exp;
            sum += div;
            exp /= 10;
        }

        //동일한 값을 찾았을 경우 출력 후 return
        if (sum == num)
        {
            std::cout << start;
            return 0;
        }
    }

    //못 찾았을경우 여기 들어오게됨
    std::cout << 0;
    return 0;
}
