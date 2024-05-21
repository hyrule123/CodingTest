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

struct int2 { 
    int n_2{}, n_1{}; 
};

int2 FibRecursive(int _n) {
    if (_n <= 2) { return { 0, 1 }; }
    int2 result = FibRecursive(--_n);
    return { result.n_1, result.n_1 + result.n_2 };
}

int Fibonacci(int _n) {
    if (_n <= 1) { return _n; }
    int2 ret = FibRecursive(_n);
    return ret.n_2 + ret.n_1;
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;
    
    int n{}; std::cin >> n;
    std::cin >> n;
    std::cout << Fibonacci(n);
    
    return 0;
}
