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

void DivideAndConquerRecursive(std::vector<int>& _orig, std::vector<int>& _temp, const size_t _start, const size_t _end)
{
    const size_t size = _end - _start + 1;
    if (size <= 1)
    {
        return;
    }

    const size_t mid = (_start + _end) / 2;

    //Divide
    DivideAndConquerRecursive(_orig, _temp, _start, mid);
    DivideAndConquerRecursive(_orig, _temp, mid + 1, _end);

    size_t lIter = _start;
    size_t rIter = mid + 1;
    size_t writeIter = lIter;

    //Conquer
    while (lIter <= mid && rIter <= _end)
    {
        //번갈아가면서 비교하고, 조건에 부합해서 값을 넣었을 경우 인덱스를 한단계씩 올려준다.
        if (_orig[lIter] <= _orig[rIter])
        {
            _temp[writeIter] = _orig[lIter];
            ++lIter;
            ++writeIter;
        }
        else
        {
            _temp[writeIter] = _orig[rIter];
            ++rIter;
            ++writeIter;
        }
    }

    //분할 갯수가 불균형하여 한 쪽이 남아있을 수도 있음 -> 남아있는 값들을 복사해준다.
    if (lIter <= mid)
    {
        for (; lIter <= mid; ++lIter)
        {
            _temp[writeIter] = _orig[lIter];
            ++writeIter;
        }
    }
    else
    {
        for (; rIter <= _end; ++rIter)
        {
            _temp[writeIter] = _orig[rIter];
            ++writeIter;
        }
    }

    //_temp에 정렬되어있는 데이터를 가져온다.
    std::copy(_temp.begin() + _start, _temp.begin() + _end + 1, _orig.begin() + _start);
}

void MergeSort(std::vector<int>& _vec)
{
    std::vector<int> temp{};
    temp.resize(_vec.size());

    DivideAndConquerRecursive(_vec, temp, 0, temp.size() - 1);
}

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{};
    std::cin >> N;

    std::vector<int> numbers{};
    numbers.resize(N);

    for (size_t i = 0; i < numbers.size(); ++i)
    {
        std::cin >> numbers[i];
    }

    MergeSort(numbers);

    for (size_t i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i] << '\n';
    }

    return 0;
}
