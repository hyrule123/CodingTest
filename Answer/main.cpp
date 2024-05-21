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
void Cantor(std::vector<char>& _arr, const size_t _start, const size_t _end) {
    size_t len = _end - _start;
    if (len <= 1) { 
        return; 
    }
    len /= 3;

    size_t part = _start + len;
    memset(_arr.data() + part, ' ', len);

    Cantor(_arr, _start, part);
    Cantor(_arr, part + len, _end);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    std::vector<char> arr{};
    int input{};
    while (std::cin >> input) {
        size_t size = 1;
        while ((--input) >= 0) {
            size *= 3;
        }
        arr.clear();
        arr.resize(size + 2, '-');
        
        arr[arr.size() - 2] = '\n';
        arr[arr.size() - 1] = '\0';
        
        Cantor(arr, 0, size);

        std::cout << arr.data();
    }
    return 0;
}
