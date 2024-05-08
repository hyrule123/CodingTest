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
constexpr const unsigned int g_tableSize = 700'009;

struct CardInfo {
    int Num;
    int Count;
};

std::vector<CardInfo> cardsTable[g_tableSize]{};

inline unsigned int Hash(int _orig) {
    unsigned int ret{};

    return (unsigned int)_orig % g_tableSize;
}

//chaining을 vector로 한 버전: 34136kb, 404ms
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{};
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int cardNum{};
        std::cin >> cardNum;
        unsigned int hash = Hash(cardNum);
        
        bool found = false;
        std::vector<CardInfo>& bucket = cardsTable[hash];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i].Num == cardNum) {
                ++(bucket[i].Count);
                found = true;
                break;
            }
        }

        if (false == found) {
            bucket.push_back(CardInfo{ cardNum, 1 });
        }
    }

    int M{};
    std::cin >> M;
    for (int i = 0; i < M; ++i) {
        int cardNum{};
        std::cin >> cardNum;
        unsigned int hash = Hash(cardNum);

        int count = 0;
        std::vector<CardInfo>& bucket = cardsTable[hash];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i].Num == cardNum) {
                count = bucket[i].Count;
                break;
            }
        }
        std::cout << count << ' ';
    }
    

    return 0;
}
