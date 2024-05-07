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

#include <array>
#include <string>


struct StringHasher {
    inline static size_t Hash(const std::string_view _str)
    {
        constexpr const size_t p = 53;//31;
        constexpr const size_t mod = 1'000'000'007;
        size_t result = 0;

        if (_str.empty()) { return result; }

        //라빈-카프 문자열 해싱, 호너의 법칙
        size_t i = _str.size() - 1;
        result = static_cast<size_t>(_str[i]);
        for (; i > 0; --i) {
            result = (result * p + _str[i]) % mod;
        }
        result = (result + _str[0]) % mod;

        return result;
    }
};

#include "HashTable.h"
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{};
    std::cin >> N;
    
    HashTable<std::string, bool, StringHasher> attendanceLog(N);
    using myPair = HashTable<std::string, bool, StringHasher>::Pair;

    constexpr const std::string_view enterMsg = "enter";

    for (size_t i = 0; i < N; ++i) {
        std::string name{};
        std::string entered{};
        std::cin >> name >> entered;

        attendanceLog[name] = (entered == enterMsg);
    }

    const auto& cont = attendanceLog.GetContainer();

    for (size_t i = 0; i < cont.size(); ++i) {
        auto& bucket = cont[i];

        auto iterEnd = bucket.end();
        for (auto iter = bucket.begin(); iter != iterEnd; ++iter) {

            if (iter->Value) {
                std::cout << iter->Key << '\n';
            } 
        }
    }
    
    

    return 0;
}
