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

//unordered_set 사용 버전
#include <unordered_set>
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}, M{};
    std::cin >> N >> M;
    std::unordered_set<std::string> stringSet{};

    std::string input{};
    input.reserve(501);
    for (size_t i = 0; i < N; ++i) {
        input.clear();
        std::cin >> input;
        stringSet.insert(input);
    }

    size_t existCount{};
    for (size_t i = 0; i < M; ++i) {
        input.clear();
        std::cin >> input;
        auto iter = stringSet.find(input);
        if (iter != stringSet.end()) {
            ++existCount;
        }
    }

    std::cout << existCount;
    return 0;
}
