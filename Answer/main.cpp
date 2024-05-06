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

inline int MakeHash(int _num) {
    return _num + 10000000;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    //기초적인 해시테이블
    std::vector<bool> sangun{};
    //-N ~ N( + 0)
    sangun.resize(20000001);
    size_t N{};
    std::cin >> N;
    for (size_t i = 0; i < N; ++i)
    {
        int num{};
        std::cin >> num;
        
        sangun[MakeHash(num)] = true;
    }

    size_t M{};
    std::cin >> M;
    for (size_t i = 0; i < M; ++i)
    {
        int num{};
        std::cin >> num;

        std::cout << sangun[MakeHash(num)] << ' ';
    }

    return 0;
}
