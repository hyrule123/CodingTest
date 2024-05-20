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
#include <array>
struct str {
    char c[12]{};
    int len{};
    int count{};

    void Reset() {
        c[0] = '\0';
        len = 0;
        count = 0;
    }
    void Set() { len = (int)std::strlen(c); count = 1; }
    bool Empty() const { return (len == 0); }
    bool operator == (const str& _other) const {
        if (len != _other.len) { return false; }

        for (int i = 0; i < len; ++i) {
            if (c[i] != _other.c[i]) { return false; }
        }

        return true;
    }
    bool operator > (const str& _other) const {
        if (count != _other.count) {
            return (count > _other.count);
        }

        else if (len > _other.len) { return true; }
        else if (len == _other.len) { 
            for (int i = 0; i < len; ++i) {
                if (c[i] == _other.c[i]) { continue; }

                return (c[i] < _other.c[i]);
            }
        }

        return false;
    }
};

bool IsPrime(size_t _num) {
    if (_num <= 1) { return false; }
    else if (_num <= 3) { return true; }

    if (_num % 2 == 0 || _num % 3 == 0) { return false; }

    for (size_t i = 5; i * i < _num; i += 5) {
        if (_num % i == 0) { return false; }
    }

    return true;
}

size_t ComputeBucketCount(size_t _num){
    _num = (size_t)(1.25f * _num);
    while (false == IsPrime(_num)) {
        ++_num;
    }
    return _num;
}

size_t Hash1(const str& _str) {
    size_t ret = 0;
    if (false == _str.Empty()) {
        ret = _str.c[0];
        for (int i = 1; i < _str.len; ++i) {
            ret = (ret * 31 + _str.c[i]) % 100'000'007;
        }
    }
    return ret;
}
size_t Hash2(const str& _str) {
    size_t ret = 0;
    if (false == _str.Empty()) {
        ret = _str.c[0];
        for (int i = 1; i < _str.len; ++i) {
            ret = (ret * 59 + _str.c[i]) % 150'000'071;
        }
    }
    return ret;
}

void DnC(std::vector<str>& _arr, std::vector<str>& _temp, const size_t _start, const size_t _end) {
    if (_start >= _end) { return; }

    const size_t mid = _start + (_end - _start) / 2;
    size_t l = _start;
    size_t r = mid + 1;

    DnC(_arr, _temp, l, mid);
    DnC(_arr, _temp, r, _end);

    size_t cursor = _start;
    while (l <= mid && r <= _end) {
        if (_arr[l] > _arr[r]) {
            _temp[cursor] = _arr[l];
            ++cursor; ++l;
        }
        else {
            _temp[cursor] = _arr[r];
            ++cursor; ++r;
        }
    }
    
    while (l <= mid) {
        _temp[cursor] = _arr[l];
        ++cursor; ++l;
    }
    while (r <= _end) {
        _temp[cursor] = _arr[r];
        ++cursor; ++r;
    }

    memcpy(_arr.data() + _start, _temp.data() + _start, sizeof(str) * (_end - _start + 1));
}

void MergeSort(std::vector<str>& _arr) {
    std::vector<str> temp(_arr.size());

    DnC(_arr, temp, 0, _arr.size() - 1);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}, M{}; std::cin >> N >> M;
    std::vector<str> table(ComputeBucketCount((size_t)N));

    //해시테이블에 넣어서 카운트 세준다.
    str input{};
    for (int i = 0; i < N; ++i) {
        input.Reset();
        std::cin >> input.c; input.Set();

        if (input.len < M) {
            input.Reset();
            continue;
        }

        size_t idx = Hash1(input) % table.size();
        size_t step = Hash2(input);

        bool found = false;
        while (false == table[idx].Empty()) {
            if (table[idx] == input) {
                ++(table[idx].count);
                found = true;
                break;
            }

            idx = (idx + step) % table.size();
        }

        if (false == found) {
            table[idx] = input;
        }
    }

    //해시테이블을 그대로 sort해서 규칙에 맞게 정렬시킨다
    MergeSort(table);

    for (size_t i = 0; i < table.size() && false == table[i].Empty(); ++i) {
        std::cout << table[i].c << '\n';
    }
    
    return 0;
}
