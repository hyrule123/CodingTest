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

using uint = unsigned int;
struct stack {
    constexpr stack(uint _capacity) : arrCont{}, capacity{ _capacity }, stackPos{-1} { arrCont = new uint[_capacity]; }
    ~stack() { delete[] arrCont; }

    inline void Insert(uint _num) { ++stackPos; arrCont[stackPos] = _num; }
    inline uint* Back() { if (0 <= stackPos) { return &(arrCont[stackPos]); } return nullptr; }
    inline void Pop() { if (0 <= stackPos) { --stackPos; } }
    inline bool NotEmpty() { return (0 <= stackPos); }

    uint* arrCont;
    uint capacity;
    int stackPos;
};

stack moneyLog(100000);

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint K{}; std::cin >> K;
    for (uint i = 0; i < K; ++i) {
        uint n{}; std::cin >> n;
        if (n) {
            moneyLog.Insert(n);
        }
        else {
            moneyLog.Pop();
        }
    }

    //inline 포인터 함수 사용 버전
    uint sum{};
    while (moneyLog.NotEmpty()) {
        sum += *(moneyLog.Back());
        moneyLog.Pop();
    }
    std::cout << sum;

    return 0;
}
