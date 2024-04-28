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

#include <array>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;
    
    std::array<std::array<bool, 100>, 100> paper{};

    int numPaper{};
    std::cin >> numPaper;

    int colorPaperSize{};
    for (int n = 0; n < numPaper; ++n)
    {
        int x{};
        int y{};

        std::cin >> x;
        std::cin >> y;

        int xEnd = x + 10;
        int yEnd = y + 10;

        for (int i = x; i < xEnd; ++i)
        {
            for (int j = y; j < yEnd; ++j)
            {
                if (false == paper[i][j])
                {
                    paper[i][j] = true;
                    ++colorPaperSize;
                }
            }
        }
    }

    std::cout << colorPaperSize;

    return 0;
}
