#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <limits>
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    using namespace std;
    
    int32_t N;
    std::cin >> N;

    int32_t min{ std::numeric_limits<int32_t>::max() };
    int32_t max{ std::numeric_limits<int32_t>::min() };

    for (int32_t i = 0; i < N; ++i)
    {
        int32_t num;
        cin >> num;
        
        if (num < min)
        {
            min = num;
        }
        if (num > max)
        {
            max = num;
        }
    }

    std::cout << min << " " << max;

    return 0;
}
