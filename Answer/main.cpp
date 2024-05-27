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

//백준 9184 컴파일타임 계산 버전(2056kb, 4ms)
#include <array>
using int3d = std::array<std::array<std::array<int, 21>, 21>, 21>;
constexpr int3d MakeArr() {
    int3d ret{};
    for (size_t a = 0; a <= 20; ++a) {
        for (size_t b = 0; b <= 20; ++b) {
            for (size_t c = 0; c <= 20; ++c) {
                if (a == 0 || b == 0 || c == 0) {
                    ret[a][b][c] = 1;
                }
                else if (a < b && b < c) {
                    ret[a][b][c] 
                        = ret[a][b][c - 1] 
                        + ret[a][b - 1][c - 1] 
                        - ret[a][b - 1][c];
                }
                else {
                    ret[a][b][c] 
                        = ret[a - 1][b][c] 
                        + ret[a - 1][b - 1][c]
                        + ret[a - 1][b][c - 1] 
                        - ret[a - 1][b - 1][c - 1];
                }
            }
        }
    }
    return ret;
}
int3d preMake = MakeArr();

int main() { 
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;
    
    while (true) {
        int a, b, c; std::cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) {
            break;
        }

        std::cout << "w(" << a << ", " << b << ", " << c << ") = ";

        if (a <= 0 || b <= 0 || c <= 0) {
            a = 0; b = 0; c = 0;
        }
        else if (a > 20 || b > 20 || c > 20) {
            a = 20; b = 20; c = 20;
        }
        
        std::cout << preMake[a][b][c] << '\n';
    }

    return 0;
}
