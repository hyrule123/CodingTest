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
struct str {
    char cont[24]{};
    size_t strLen{};

    bool Empty() const { return (strLen == 0); }
    bool operator == (const str& _other) const {
        if (strLen != _other.strLen) { return false; }

        if (false == Empty()) {
            for (size_t i = 0; i < strLen; ++i) {
                if (cont[i] != _other.cont[i]) {
                    return false;
                }
            }
        }
        return true;
    }
};

constexpr size_t bucketSize = 3001;
constexpr size_t p = 31;
size_t Hash(const str& _str) {
    size_t ret{};
    if (false == _str.Empty()) {
        ret = (size_t)_str.cont[0];
        for (size_t i = 1; i < _str.strLen; ++i) {
            ret = (ret * p + _str.cont[i]) % bucketSize;
        }
    }
    return ret;
}

struct infectData {
    str name{};
    bool infected{};
};
std::string_view name("hi");
constexpr str ChongChong = { "ChongChong", sizeof("ChongChong") - 1 };

#include <array>
std::array <infectData, bucketSize> infectTable{};

infectData& GetData(const str& _str) {
    size_t hash = Hash(_str);

    while (false == infectTable[hash].name.Empty()) {
        if (infectTable[hash].name == _str) {
            return infectTable[hash];
        }
        ++hash;
        hash %= infectTable.size();
    }

    infectTable[hash].name = _str;
    
    return infectTable[hash];
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;
    str a{}; str b{};
    int InfectedCount = 1; //ChongChong
    for (int i = 0; i < N; ++i) {
        std::cin >> a.cont >> b.cont;
        a.strLen = std::strlen(a.cont);
        b.strLen = std::strlen(b.cont);

        infectData& dataA = GetData(a);
        infectData& dataB = GetData(b);

        if (dataA.name == ChongChong) { dataA.infected = true; }
        else if (dataB.name == ChongChong) { dataB.infected = true; }

        if (dataA.infected != dataB.infected) {
            dataA.infected = true;
            dataB.infected = true;
            ++InfectedCount;
        }
    }

    std::cout << InfectedCount;

    return 0;
}
