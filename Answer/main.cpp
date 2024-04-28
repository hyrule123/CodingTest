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

    //n회: 점 x개, 사각형 y개
    //초기상태: 점4(2*2),   사각형1(4^0)
    //1번: 점9(3*3),       사각형4(4^1)
    //2번: 점25(5*5),      사각형16(4^2)
    //3번: 점81(9*9),      사각형64(4^3)
    //4번: 점x개(17*17)
    //n번: (2^n + 1)^2

    int N{};
    std::cin >> N;
    
    int answer{ 1 };
    for (int i = 0; i < N; ++i)
    {
        answer *= 2;
    }
    answer += 1;

    std::cout << PowInt(answer, 2);

    return 0;
}
