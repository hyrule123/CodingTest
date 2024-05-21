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
#include <string>

void SetStar(std::vector<std::vector<char>>& _sqre, const size_t _startX, const size_t _startY, size_t _length) {
    if (_length <= 1) { return; }
    _length /= 3;
    
    size_t xErase = _startX + _length;
    size_t xEraseEnd = xErase + _length;
    size_t yErase = _startY + _length;
    size_t yEraseEnd = yErase + _length;

    //중간 뚫기
    for (size_t y = yErase; y < yEraseEnd; ++y) {
        memset(_sqre[y].data() + xErase, ' ', _length);
    }

    //8방향 재귀
    for (size_t x = _startX, xEnd = xEraseEnd + _length; x < xEnd; x += _length) {
        for (size_t y = _startY, yEnd = yEraseEnd + _length; y < yEnd; y += _length) {
            //방금 했던 중간부분은 호출 안해도 됨
            if (x == xErase && y == yErase) { continue; }
            SetStar(_sqre, x, y, _length);
        }
    }
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}; std::cin >> N;
    
    std::vector<std::vector<char>> square;
    square.resize(N);
    size_t charSize = N + 2;
    for (size_t i = 0; i < N; ++i) {
        square[i].resize(charSize, '*');
        square[i][charSize - 2] = '\n';
        square[i][charSize - 1] = '\0';
    }

    SetStar(square, 0, 0, N);

    for (size_t i = 0; i < N; ++i) {
        std::cout << square[i].data();
    }

    return 0;
}
