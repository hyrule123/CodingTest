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

    using namespace std;

    // 1/1 -> 1/2 -> 2/1 -> 3/1 -> 2/2 -> 1/3 -> 1/4 -> 2/3 -> 3/2 -> 1/4
    // 계차수열(등차: 1)

    int X{};
    std::cin >> X;
    
    int diff{ 1 };
    int lineCount{ 0 };
    while (0 < X)
    {
        X -= diff;
        diff += 1;
        ++lineCount;
    }
    
    //한 줄 안에서의 위치
    int posInLine = X + lineCount;

    int num1{ lineCount + 1 - posInLine };
    int num2{ lineCount + 1 - num1 };

    //짝수일때는 오른쪽 위부터, 홀수일때는 왼쪽 아래부터
    if (1 == lineCount % 2)
    {
        std::cout << num1 << '/' << num2;
    }
    else
    {
        std::cout << num2 << '/' << num1;
    }
    return 0;
}
