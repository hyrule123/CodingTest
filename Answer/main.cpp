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

int GetDotNumRecursive(int _dotNumber, const int _targetLevel, int _currentLevel = 0)
{
    if (_currentLevel < _targetLevel)
    {
        return GetDotNumRecursive(2 * _dotNumber - 1, _targetLevel, ++_currentLevel);
    }
    
    return _dotNumber;
}
inline int PowInt(int _base, int _exponent)
{
    int ret = 1;
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

    //1, 7, 19, 37
    //  6, 12, 18, 24, 36
    //S(1) = 1
    //S(n) = S(n-1) + 6(n-1)
    //매 바퀴당 갯수는 6n개
    //시작 숫자: 시그마(1~n)1 + 6n 단위로 증가

    int N{};
    std::cin >> N;

    int prev{ 1 };
    int diff{ 6 };
    int count{ 1 };
    
    while (prev < N)
    {
        prev += diff;
        diff += 6;
        ++count;
    }

    std::cout << count;
    return 0;
}
