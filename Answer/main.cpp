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
//////////////////


#include <vector>
void Recursive(std::vector<int>& _arr, const int _range, const size_t _max) {
    if (_arr.size() == _max) {
        for (size_t i = 0; i < _arr.size(); ++i) {
            std::cout << _arr[i] << ' ';
        }
        std::cout << '\n';
        return;
    }

    for (int i = 1; i <= _range; ++i) {
        _arr.push_back(i);
        Recursive(_arr, _range, _max);
        _arr.pop_back();
    }
}

int main() { READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    int N{}; size_t M{}; std::cin >> N >> M;
    std::vector<int> arr;
    arr.reserve(M);
    Recursive(arr, N, M);

    return 0;
}
