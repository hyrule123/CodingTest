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

constexpr bool IsPrime(size_t _num) {
    if (_num <= 1) {
        return false;
    }

    for (size_t i = 2; i <= _num / 2; ++i) {
        if (_num % i == 0) {
            return false;
        }
    }
    return true;
}

constexpr size_t NextPrime(size_t _num) {
    while (false == IsPrime(_num)) {
        ++_num;
    }
    return _num;
}

#include <vector>


class HashTable {
    static constexpr const size_t bucketCount = 250007;
public:
    HashTable() 
        : m_table{}
    { m_table.resize(bucketCount); }
    ~HashTable() {};

    inline size_t Hash(int _num) {
        return (size_t)_num % bucketCount;
    }

    inline void Insert(int _key) {
        size_t hash = Hash(_key) % m_table.size();
        m_table[hash].push_back(_key);
    }

    inline int* Find(int _key) {
        size_t hash = Hash(_key) % m_table.size();

        std::vector<int>& bucket = m_table[hash];

        if (false == m_table.empty()) {
            for (size_t i = 0; i < bucket.size(); ++i) {
                if (bucket[i] == _key) {
                    return &(bucket[i]);
                }
            }
        }

        return nullptr;
    }

private:
    std::vector<std::vector<int>> m_table;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t numA{}, numB{};
    std::cin >> numA >> numB;

    HashTable setA{};
    for (size_t i = 0; i < numA; ++i) {
        int input{};
        std::cin >> input;
        setA.Insert(input);
    }

    size_t intersectionCount{};
    for (size_t i = 0; i < numB; ++i) {
        int input{};
        std::cin >> input;
        int* found = setA.Find(input);
        if (found) {
            ++intersectionCount;
        }
    }

    //합집합 갯수 - 교집합 갯수
    std::cout << numA + numB - 2 * intersectionCount;

    return 0;
}
