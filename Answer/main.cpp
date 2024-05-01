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
#include <limits>

#include <string>
#include <vector>
#include <array>

//나머지를 통해 새당 위치의 값을 알 수 있다.
//B로 시작하는 체스판 패턴일 때
char GetColor_BStart(size_t _r, size_t _c)
{
    constexpr std::array<std::array<char, 2>, 2> pattern = { { {'B', 'W'}, { 'W', 'B'} } };
    return pattern[_r % 2][_c % 2];
}

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t rows{}, cols{};
    std::cin >> rows >> cols;

    std::vector<std::string> chessBoard{};
    chessBoard.resize(rows);

    for (auto& r : chessBoard)
    {
        r.reserve(cols + 1);
        std::cin >> r;
    }

    size_t minChanges{ std::numeric_limits<size_t>::max() };

    size_t rowEnd = rows - 8;
    size_t colEnd = cols - 8;
    for (size_t rowStart = 0; rowStart <= rowEnd; ++rowStart)
    {
        for (size_t colStart = 0; colStart <= colEnd; ++colStart)
        {
            //B로 시작할떄와 W로 시작할때 각각 변경해야 하는 갯수
            size_t changes_BStart{};
            size_t changes_WStart{};

            //8x8 체스판 각각 테스트해준다.
            size_t rTestEnd = rowStart + 8;
            size_t cTestEnd = colStart + 8;
            for (size_t r = rowStart; r < rTestEnd; ++r)
            {
                for (size_t c = colStart; c < cTestEnd; ++c)
                {
                    if (GetColor_BStart(r, c) == chessBoard[r][c])
                    {
                        ++changes_BStart;
                    }
                    else
                    {
                        ++changes_WStart;
                    }
                }
            }

            minChanges = std::min(minChanges, changes_BStart);
            minChanges = std::min(minChanges, changes_WStart);
        }
    }
    std::cout << minChanges;

    return 0;
}
