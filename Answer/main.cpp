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
void DigitRecursive(std::vector<int>& _inUse, const int _range, const size_t _digitMax) {
    if (_inUse.size() == _digitMax) { 
        for (size_t i = 0; i < _inUse.size(); ++i) {
            std::cout << _inUse[i] << ' ';
        }
        std::cout << '\n';
        return; 
    }

    for (int i = 1; i <= _range; ++i) {
        bool cont = false;
        for (size_t j = 0; j < _inUse.size(); ++j) {
            if (_inUse[j] == i) {
                cont = true;
                break;
            }
        }
        if (cont) { continue; }
        _inUse.push_back(i);
        DigitRecursive(_inUse, _range, _digitMax);
        _inUse.pop_back();
    }
}

void Digit(int N, size_t M) {
    std::vector<int> inUse{};
    inUse.reserve(M);
    DigitRecursive(inUse, N, M);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;
    
    int N{}; size_t M{}; std::cin >> N >> M;
    Digit(N, M);

    return 0;
}
