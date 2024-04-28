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
    
    int N{}, M{};
    std::cin >> N >> M;
    int matSize = N * M;

    //정석 이중포인터로 해보기
    int** matSum{};

    //1차 동적할당
    matSum = new int*[N];
    memset(matSum, 0, sizeof(int*) * N);

    for (int i = 0; i < N; ++i)
    {
        //2차 동적할당
        matSum[i] = new int[M];
        memset(matSum[i], 0, sizeof(int) * M);
    }

    for (int numMat = 0; numMat < 2; ++numMat)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                int input{};
                std::cin >> input;
                matSum[i][j] += input;
            }
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cout << matSum[i][j] << ' ';
        }

        std::cout << '\n';
    }
    
    //동적할당 메모리 해제
    for (int i = 0; i < N; ++i)
    {
        delete[] matSum[i];
    }
    delete[] matSum;
    return 0;
}
