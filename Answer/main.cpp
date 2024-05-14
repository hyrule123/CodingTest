#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

////////////////////////////
#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
////////////////////////////

#include <vector>

inline double ABS(double _in) {
    return (_in < 0.0 ? -_in : _in);
}

//babylonian algorithm
using uint = unsigned int;
uint SQRT(uint _num) {
    if (_num <= 1) { return _num; }

    double n = (double)_num;
    double a = n / 2.0;
    constexpr double precision = 0.000001;
    while (ABS(a * a - n) > precision) {
        a = (a + n / a) / 2.0;
    }

    return (uint)a;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    
    uint N{}; std::cin >> N;
    
    //2: 1 2 열 닫
    //3: 1 3 -> 열 닫
    //4: 1 2 4 -> 열 닫 열
    //5: 1 5 닫
    //6: 1 2 3 6 닫
    //7: 1 7 닫
    //8: 1 2 4 8 닫
    //약수 개수가 짝수->닫힘
    //약수 개수가 홀수->열림
    //약수 개수가 짝수이려면->제곱수여야 함
    //범위 1 ~ N 사이의 제곱수의 갯수
    std::cout << SQRT(N);

    return 0;
}
