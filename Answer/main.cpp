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
#include <array>

inline size_t Hash(const std::array<char, 21>& _str) {
    size_t ret = _str[0];
    if (ret == 0) {
        return ret;
    }

    constexpr const size_t prime = 31;
    constexpr const size_t mod = static_cast<size_t>(1e9 + 9);

    for (size_t i = 1; _str[i] != '\0'; ++i) {
        ret = ((ret * prime) + _str[i]) % mod;
    }

    return ret;
}


inline bool IsPrime(size_t _n) {
    if (_n <= 1) {
        return false;
    }
    for (size_t i = 2; i * i <= _n; ++i) {
        if (_n % i == 0) {
            return false;
        }
    }
    return true;
}

inline int GetNumberIfInt(const std::array<char, 21>& _str) {
    int ret = -1;

    if (_str[0] == '\0') {
        return ret;
    }
    //첫번째 자리만 검사(포켓몬 이름에 숫자는 없다고 했음)
    else if (_str[0] < '0' || '9' < _str[0]) {
        return ret;
    }

    int end = 0;
    while (_str[end] != '\0') {
        ++end;
    }

    ret = _str[0] - '0';
    for (int i = 1; i < end; ++i) {
        ret = ret * 10 + (_str[i] - '0');
    }

    return ret;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}, M{};
    std::cin >> N >> M;

    std::vector<std::array<char, 21>> arrNames{};
    arrNames.resize(N);

    //Key: 문자열, Value: 도감 번호
    std::vector<int>    hashTable{};

    //버킷 사이즈를 전체 갯수의 1.2배 정도로 잡아준다.
    size_t hashTableSize = (size_t)((float)N * 1.2f);
    while (false == IsPrime(hashTableSize)) {
        ++hashTableSize;
    }
    hashTable.resize(hashTableSize, -1);

    {
        std::array<char, 21> temp{};
        std::cin.getline(temp.data(), 21);
    }

    //데이터 입력 및 저장
    for (size_t i = 0; i < N; ++i) {
        std::cin.getline(arrNames[i].data(), 21);

        size_t hash = Hash(arrNames[i]) % hashTableSize;
        //linear probing
        while (hashTable[hash] != -1) {
            ++hash;
            if (hash >= hashTableSize) {
                hash = 0;
            }
        }

        hashTable[hash] = (int)i;
    }

    //검사용 데이터 입력 및 출력
    std::array<char, 21> input{};
    for (size_t i = 0; i < M; ++i) {
        input[0] = '\0';
        std::cin.getline(input.data(), 21);

        //정수인지 문자열인지 확인
        int result = GetNumberIfInt(input);

        //문자열이라면
        if (-1 == result) {
            size_t hash = Hash(input) % hashTableSize;

            //linear probing
            while (0 != strcmp(input.data(), arrNames[hashTable[hash]].data())) {
                ++hash;
                if (hash >= hashTableSize) {
                    hash = 0;
                }
            }

            //도감번호를 출력
            std::cout << hashTable[hash] + 1 << '\n';
        }

        //도감 번호라면
        else {
            //문자열을 출력
            std::cout << arrNames[result - 1].data() << '\n';
        }
    }

    return 0;
}
