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

    int A, B, V;
    std::cin >> A >> B >> V;

    //매일 올라갈수있는 높이
    A -= B;

    //마지막 결승점 도달에는 B만큼 떨어지는게 의미가 없으므로
    //(1 더해서 빼는 이유: 나눠떨어지는거 방지)
    V -= (B + 1);

    std::cout << V / A + 1;

    return 0;
}
