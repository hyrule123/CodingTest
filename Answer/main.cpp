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
#include <string>
constexpr size_t bucketSize = 120001;

struct str {
    char cont[24]{};
    size_t strLen{};
    bool Empty() const { return (0 == strLen); }

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
size_t Hash(const str& _str) {
    size_t ret{};

    constexpr size_t p = 31;

    if (false == _str.Empty()) {
        ret = (size_t)_str.cont[0];
        for (size_t i = 1; i < _str.strLen; ++i) {
            ret = (ret * p + (size_t)_str.cont[i]) % bucketSize;
        }
    }

    return ret;
}

constexpr str ENTER = { "ENTER", 5 };

struct userLog {
    str name;
    int welcomeCount{};
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;

    std::vector<userLog> chatLog{};
    chatLog.resize(bucketSize);

    int enterCount{};   //들어온 사람 숫자
    int gomgomCount{};  //곰곰티콘 쓴 사람 숫자
    str input{};
    for (int i = 0; i < N; ++i) {
        input.cont[0] = '\0';
        std::cin >> input.cont;
        input.strLen = std::strlen(input.cont);

        if (input == ENTER) {
            ++enterCount;
            continue;
        }

        size_t hash = Hash(input);

        bool found = false;
        while (false == chatLog[hash].name.Empty()) {
            if (chatLog[hash].name == input) {
                found = true;
                
                //인사한횟수가 들어온 사람수보다 적다면, 인사를 한것임
                if (enterCount > chatLog[hash].welcomeCount) {
                    ++gomgomCount;

                    //인사횟수 갱신
                    chatLog[hash].welcomeCount = enterCount;
                }

                break;
            }

            ++hash;
            hash %= chatLog.size();
        }

        //못찾았다면, 즉 처음 메시지를 보낸사람이라면 등록후 gomgomCount 사용처리
        if (false == found) {
            chatLog[hash].name = input;
            chatLog[hash].welcomeCount = enterCount;
            ++gomgomCount;
        }
    }

    std::cout << gomgomCount;

    return 0;
}
