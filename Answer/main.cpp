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

#include <vector>

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;

    int N{};
    std::cin >> N;
    
    int maxStar = 1 + 2 * (N - 1);
    int centerIdx = maxStar / 2;

    std::vector<std::string> stars(N);
    for (size_t i = 0; i < stars.size(); ++i)
    {
        int slen = centerIdx + i + 2;
        stars[i].resize(slen, ' ');
        memset(stars[i].data() + (centerIdx - i), '*', 1 + i * 2);
        stars[i][slen - 1] = '\n';
        std::cout << stars[i];
    }

    for (int i = (int)stars.size() - 2; i >= 0; --i)
    {
        std::cout << stars[i];
    }
    

    return 0;
}
