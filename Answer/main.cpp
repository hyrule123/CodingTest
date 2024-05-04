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



int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    struct Coord { int x, y; };
    struct CoordAscending
    {
        using Type = Coord;
        static inline bool Compare(const Type& _a, const Type& _b) {
            if (_a.x == _b.x) {
                return _a.y <= _b.y;
            }

            return _a.x < _b.x;
        }
    };

    std::size_t N{};
    std::cin >> N;

    std::vector<Coord> arrCoord{};
    arrCoord.resize(N);

    for (size_t i = 0; i < N; ++i) {
        std::cin >> arrCoord[i].x >> arrCoord[i].y;
    }

    QuickSelect<CoordAscending>(arrCoord, 0);

    for (size_t i = 0; i < N; ++i) {
        std::cout << arrCoord[i].x << ' ' << arrCoord[i].y << '\n';
    }
    
    return 0;
}
