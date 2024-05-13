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

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using uint = unsigned int;

    uint smallest{};
    uint biggest{};
    std::vector<uint> inputs{};
    std::vector<uint> inputsEnd{};
    while (true) {
        uint input{};
        std::cin >> input;

        if (0 == input) { break; }

        inputs.push_back(input);
        if (smallest > input) { smallest = input; }

        input *= 2;
        if (biggest < input) { biggest = input; }
        inputsEnd.push_back(input);
    }

    std::vector<bool> sieve{};
    sieve.reserve(biggest + 1);
    sieve.resize(biggest + 1, true);

    if (sieve.size() >= 1) { sieve[0] = false; }
    if (sieve.size() >= 2) { sieve[1] = false; }

    for (size_t p = 2, pPow2{}; (pPow2 = p * p) <= biggest; ++p) {
        if (sieve[p]) {
            for (size_t i = pPow2; i <= biggest; i += p) {
                sieve[i] = false;
            }
        }
    }

    for (size_t i = 0; i < inputs.size(); ++i) {
        size_t counts{};
        const size_t inputEnd = inputsEnd[i];
        for (size_t j = inputs[i] + 1; j <= inputEnd; ++j) {
            if (sieve[j]) {
                ++counts;
            }
        }

        std::cout << counts << '\n';
    }

    return 0;
}
