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
    
    constexpr const char* grades[] = { "A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F" };
    constexpr size_t gradeCount = sizeof(grades) / sizeof(const char*);
    constexpr float gradeScores[] = { 4.5f, 4.f, 3.5f, 3.f, 2.5f, 2.f, 1.5f, 1.f, 0.f };

    static_assert(gradeCount == (sizeof(gradeScores) / sizeof(float)));


    //학점: credit
    //과목평점: gradeScore

    //학점 * 과목평점
    float credit_x_gradeScore_sum{ 0.f };

    //학점의 총합
    float creditSum{ 0.f };
    for (int i = 0; i < 20; ++i)
    {
        char cls[51]{};
        float credit{};
        char grade[3]{};

        std::cin >> cls >> credit >> grade;

        for (size_t j = 0; j < gradeCount; ++j)
        {
            if (0 == strcmp(grade, grades[j]))
            {
                credit_x_gradeScore_sum += credit * gradeScores[j];
                creditSum += credit;
            }
        }
    }

    std::cout << (credit_x_gradeScore_sum / creditSum);

    return 0;
}
