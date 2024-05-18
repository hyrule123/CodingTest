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

using uint = std::uint32_t;
uint GCD(uint _a, uint _b) {

    while (_b != 0) {
        uint r = _a % _b;
        _a = _b;
        _b = r;
    }

    return _a;
}

uint LCM(uint _a, uint _b) {
    //a * b / GCD(a,b) -> overflow 방지를 위해 a / gcd(a, b) * b
    return (_a / GCD(_a, _b) * _b);
}

//오답 코드//
//이유: 최소공배수로 구할 시 소수들의 곱으로 표현되는 수가 정답인 경우 예외가 생길 수 있음.
//ex: 7 49 343의 최소공배수는 686 -> 7 49 343 이외에도 다른 약수를 가지고 있다.
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint divisorCount{}; std::cin >> divisorCount;

    if (1 == divisorCount) {
        uint input{}; std::cin >> input;
        std::cout << input * input;
    }
    else {
        uint lcm{}; std::cin >> lcm;
        uint biggest = lcm;
        uint smallest = lcm;
        for (uint i = 1; i < divisorCount; ++i) {
            uint input{}; std::cin >> input;
            lcm = LCM(lcm, input);
            if (biggest < input) { biggest = input; }
        }
        //제일 큰 숫자도 N이 아닌 약수이므로
        lcm = LCM(lcm, biggest * 2);

        std::cout << lcm;
    }

    return 0;
}
