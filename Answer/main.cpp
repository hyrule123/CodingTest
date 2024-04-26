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
int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    //line 1
    unsigned int N;
    std::cin >> N;
    (void)std::cin.get();

    //line 2 미리 받아놓기
    std::string l2{};
    std::getline(std::cin, l2);
    std::stringstream line2{l2};

    //line 3
    int target;
    std::cin >> target;

    //line 2
    unsigned int count{0u};
    for (unsigned int i = 0u; i < N; ++i)
    {
        int num;
        line2 >> num;

        if (num == target)
        {
            ++count;
        }
    }
    std::cout << count;

    return 0;
}
