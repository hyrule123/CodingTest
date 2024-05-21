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
int DnC(std::vector<int>& _vec, std::vector<int>& _temp, const size_t _start, const size_t _end, int& _nthWrite) {
    if (_start >= _end) { return -1; }


    const size_t mid = _start + (_end - _start) / 2;
    size_t l = _start;
    size_t r = mid + 1;

    int ret = 0;
    ret = DnC(_vec, _temp, l, mid, _nthWrite);
    if (-1 != ret) { return ret; }

    ret = DnC(_vec, _temp, r, _end, _nthWrite);
    if (-1 != ret) { return ret; }

    size_t cursor = _start;
    while (l <= mid && r <= _end) {
        if (_vec[l] <= _vec[r]) {
            _temp[cursor] = _vec[l];
            ++cursor; ++l;
        }
        else {
            _temp[cursor] = _vec[r];
            ++cursor; ++r;
        }
    }

    while (l <= mid) {
        _temp[cursor] = _vec[l];
        ++cursor; ++l;
    }
    while (r <= _end) {
        _temp[cursor] = _vec[r];
        ++cursor; ++r;
    }

    for (size_t i = _start; i <= _end; ++i) {
        _vec[i] = _temp[i];
        --_nthWrite;
        if (_nthWrite == 0) {
            return _vec[i];
        }
    }

    return -1;
}

int MergeSortNth(std::vector<int>& _vec, int _nthWrite) {
    if (_vec.size() < 2) { return -1; }

    std::vector<int> temp(_vec.size());

    return DnC(_vec, temp, 0, temp.size() - 1, _nthWrite);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}; int K{}; std::cin >> N >> K;
    std::vector<int> vec(N);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> vec[i];
    }

    std::cout << MergeSortNth(vec, K);

    return 0;
}
