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
#include <vector>
using uint = unsigned int;
constexpr uint bucketSize = 10007;
struct pair {
    int val;
    int count;
};


std::array<std::vector<pair>, bucketSize> table;
struct HashTable {
    uint Hash(int _key) {
        return ((uint)_key / bucketSize);
    }
    pair& operator[] (int _key) {
        std::vector<pair>& bucket = table[Hash(_key)];
        if (false == bucket.empty()) {
            for (size_t i = 0; i < bucket.size(); ++i) {
                if (bucket[i].val == _key) {
                    return bucket[i];
                }
            }
        }
        bucket.push_back(pair{ _key, 0 });
        return bucket.back();
    }
};


//참고: N은 홀수
//1. arithMean: 입력받는 동안 sum값을 기록, 마지막에 (float)N으로 나눠주고 round(모든값의 합 <= 2억 -> int로 처리 가능)
//2. median: 입력받은 후 처리해야 함
//3. mode: 입력받는동안 해시테이블에 기록
//4. range: 입력받으면서 최댓값, 최솟값 

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int arithMean{};
    int max = std::numeric_limits<int>::min();
    int min = std::numeric_limits<int>::max();

    HashTable modeTable{};

    int N{}; std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int input{}; std::cin >> input;

        arithMean += input;
        if (max < input) { max = input; }
        if (min > input) { min = input; }

        ++(modeTable[input].count);
    }
    arithMean /= N;
    std::cout << arithMean << '\n';

    
    pair mode{};
    for (uint i = 1; i < bucketSize; ++i) {
        std::vector<pair>& bucket = table[i];
        if (false == bucket.empty()) {
            for (size_t j = 0; j < bucket.size(); ++j) {
                if (bucket[j].count > mode.count) {
                    mode = bucket[j];
                }
            }
        }
    }

    
    return 0;
}
