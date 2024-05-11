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

#include <array>
#include <string>
#include <string_view>
constexpr size_t bucketSize = 1259;
constexpr size_t GetPrime(size_t _num) {
    if (_num <= 1) {
        return 2;
    }
    else if (_num <= 3) {
        return _num;
    }

    while (++_num) {
        if (0 == _num % 2 || 0 == _num % 3) {
            continue;
        }

        bool found = true;
        for (size_t i = 5; i * i <= _num; i += 6) {
            if (0 == _num % i || 0 == _num % (i + 2)) {
                found = false;
                break;
            }
        }

        if (found) { break; }
    }

    return _num;
}

inline size_t Hash(const std::string_view _str) {
    size_t ret = 0;

    //Empty 예외처리 안해도 됨
    if (1 == _str.size()) {
        ret = _str[0] % bucketSize;
    }
    else {
        ret = (size_t)_str[0];
        for (size_t i = 1; i < _str.size(); ++i) {
            ret = ((ret * 2) % bucketSize + _str[i]) % bucketSize;
        }
    }
    
    return ret;
}

//Rabin-Karp fingerprint
inline size_t RollHash(size_t _orig, size_t _strLen, char _eraseChar, char _endChar) {
    if (1 == _strLen) {
        return _endChar % bucketSize;
    }

    size_t ret = _eraseChar % bucketSize;
    for (size_t i = 1; i < _strLen; ++i) {
        ret = ret * 2 % bucketSize;
    }

            //음수 방지용
    return (((_orig + bucketSize) - ret) * 2 % bucketSize + _endChar) % bucketSize;
}

std::array<std::string_view, bucketSize> HashTable{};

//로직: 전체 경우의 수에서 중복되는 경우의 수를 하나씩 빼주기(Rabin-Karp Roll Hash 활용)
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    std::string input{};
    input.reserve(1001);
    std::cin >> input;

    //문자열에서 가능한 전체 케이스(sum 1 + 2 + ... + n)
    //문자열 1000개일 때 500500개 가능
    size_t possibleCases = (1 + input.size()) * input.size() / 2;

    
    //문자열의 길이 1개 ~ n개 확인
    for (size_t checkLen = 1, maxLen = input.size() - 1; checkLen <= maxLen; ++checkLen) {
        //매 순회마다 HashTable 초기화
        HashTable.fill(std::string_view());

        //한칸씩 오른쪽으로 이동해가면서 확인

        //0번째 인덱스 처리
        std::string_view check(input.data(), checkLen); //substr
        size_t hash = Hash(check);   //prevhash
        HashTable[hash] = check;
        for (size_t i = 1, end = input.size() - checkLen; i <= end; ++i) {
            char toErase = check[0];
            check = std::string_view(input.data() + i, checkLen);
            char toAdd = check.back();

            //RollHash를 통해 해쉬 연산량 최대한 줄여준다
            hash = RollHash(hash, checkLen, toErase, toAdd);

            //해쉬 충돌 체크(linear probing)
            bool found = false;
            while (false == HashTable[hash].empty()) {

                //중복된 값을 넣었을 경우에는 전체 경우의 수에서 빼준다.
                if (HashTable[hash] == check) {
                    --possibleCases;
                    found = true;
                    break;
                }

                
                ++hash;
                if (hash >= bucketSize) {
                    hash = 0;
                }
            }

            if (found) {
                continue;
            }
            
            //처음 발견한 해시값일경우 테이블에 추가
            HashTable[hash] = check;
        }
    }

    std::cout << possibleCases;
    return 0;
}
