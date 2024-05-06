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

//linear probing 사용, 무조건 전체 집합의 원소수보다 커야 하므로 20000을 넘는 첫번째 소수인 20011로 잡았음
constexpr const size_t g_maxLen = 504;
constexpr const size_t g_mod = 20011;
struct alignas(8) tKey
{
    char Data[g_maxLen];
    std::string_view Str;
    bool IsColliding;
};
std::array<tKey, g_mod> g_hashTable;

inline size_t HashString(const std::string_view _str)
{
    constexpr const size_t p = 31;
    size_t result = -1;

    if (_str.empty()) { return result; }

    //라빈-카프 문자열 해싱, 호너의 법칙
    size_t i = _str.size() - 1;
    result = static_cast<size_t>(_str[i]);
    for (; i > 0; --i)
    {
        result = (result * p + _str[i]) % g_mod;
    }
    result = (result + _str[0]) % g_mod;

    return result;
}


size_t Insert(const std::string_view _str)
{
    const size_t origHash = HashString(_str);
    size_t hash = origHash;

    //해시 충돌 처리(linear probing)
    while ('\0' != g_hashTable[hash].Data[0]) {
        g_hashTable[hash].IsColliding = true;

        ++hash;
        if (hash >= g_mod) { hash = 0; }
    }

    //중복 string은 없다고 했으므로 중복 검사는 생략한다.
    tKey& key = g_hashTable[hash];
    memcpy(key.Data, _str.data(), _str.size());
    key.Data[_str.size()] = '\0';
    key.Str = key.Data;

    if (origHash != hash) { key.IsColliding = true; }

    return hash;
}

size_t Find(const std::string_view _str)
{
    size_t hash = HashString(_str);
    
    //충돌중일 때는 문자열을 직접 비교
    while (g_hashTable[hash].IsColliding) {
        if (_str == g_hashTable[hash].Str) {
            return hash;
        }

        ++hash;
        if (hash >= g_mod) { hash = 0; }
    }

    //hash 인덱스에 저장된 문자열과 비교 후 일치하지 않을 경우 -1을 반환
    if (_str != g_hashTable[hash].Str) {
        hash = -1;
    }
    return hash;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}, M{};
    std::cin >> N >> M;

    std::string input{};
    input.reserve(501);
    for (size_t i = 0; i < N; ++i) {
        input.clear();
        std::cin >> input;
        Insert(input);
    }

    size_t existCount{};
    for (size_t i = 0; i < M; ++i) {
        input.clear();
        std::cin >> input;
        size_t result = Find(input);
        if (static_cast<size_t>(-1) != result) {
            ++existCount; 
        }
    }
    
    std::cout << existCount;
    return 0;
}
