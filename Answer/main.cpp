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

#include <string>

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    std::string input{};
    input.reserve(1000);
    std::cin >> input;

    //문자열에서 가능한 전체 케이스(sum 1 + 2 + ... + n)
    //문자열 1000개일 때 500500개 가능
    size_t cases = (1 + input.size()) * input.size() / 2;
    constexpr size_t c = (1 + 1000) * 1000 / 2;
    
    //'%' 연산자는 *, /와 동일한 우선순위로 우측으로 진행된다.
    int test = 100 * 2 % 7;

    //'abrac'의 일부 문자열에 대한 테스트

    //'abra'
    size_t hashabra = ((('a' * 2 % 7 + 'b') * 2 % 7 + 'r') * 2 % 7) + 'a';

    //roll hash
    size_t hashbrac = (hashabra - ((('a' * 2 % 7) * 2 % 7) * 2 % 7)) * 2 % 7 + 'c';

    //'brac'
    size_t hashbrac2 = ((('b' * 2 % 7 + 'r') * 2 % 7 + 'a') * 2 % 7) + 'c';

    //hashbrac == hashbrac2

    return 0;
}
