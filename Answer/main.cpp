#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//재귀함수 + 메모 버전(2056kb, 8ms)
int memo[21][21][21]{};
int w(int _a, int _b, int _c) {
    int& m = memo[_a][_b][_c];
    if (m) {
        return m;
    }

    if (_a == 0 || _b == 0 || _c == 0) {
        m = 1;
        return m;
    }
    else if (_a < _b && _b < _c) {
        m = w(_a, _b, _c - 1) + w(_a, _b - 1, _c - 1) - w(_a, _b - 1, _c);
        return m;
    }

    m = w(_a - 1, _b, _c) + w(_a - 1, _b - 1, _c) + w(_a - 1, _b, _c - 1) - w(_a - 1, _b - 1, _c - 1);
    return m;
}

int main() {
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    while (true) {
        int a, b, c; std::cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) { break; }

        std::cout << "w(" << a << ", " << b << ", " << c << ") = ";
        if (a <= 0 || b <= 0 || c <= 0) {
            std::cout << 1 << '\n';
            continue;
        }
        else if (a > 20 || b > 20 || c > 20) { a = 20; b = 20; c = 20; }

        std::cout << w(a, b, c) << '\n';
    }

    return 0;
}
