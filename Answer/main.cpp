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

    std::vector<float> scores((size_t)N);

    float maxScore = 0;
    for (size_t i = 0; i < scores.size(); ++i)
    {
        std::cin >> scores[i];
        if (maxScore < scores[i])
        {
            maxScore = scores[i];
        }
    }
    
    float avg{};
    for (size_t i = 0; i < scores.size(); ++i)
    {
        avg += scores[i] / maxScore * 100.f;
    }
    std::cout << avg / (float)N;
    
    return 0;
}
