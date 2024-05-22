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

void AscendingRecursive(std::vector<int>& _before, const int _range, const size_t _max) {
    if (_before.size() == _max) {
        for (size_t i = 0; i < _before.size(); ++i) {
            std::cout << _before[i] << ' ';
        }
        std::cout << '\n';
        return;
    }


    for (int i = (_before.empty() ? 0 : _before.back()) + 1; i <= _range; ++i) {
        _before.push_back(i);
        AscendingRecursive(_before, _range, _max);
        _before.pop_back();
    }
}

void Ascending(int _n, size_t _m) {
    std::vector<int> before;
    before.reserve(_n);

    AscendingRecursive(before, _n, _m);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; size_t M{}; std::cin >> N >> M;
    Ascending(N, M);

    return 0;
}
