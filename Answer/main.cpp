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
#include <type_traits>


void MinHeapify(std::vector<int>& _arr, size_t _size, size_t _idx) 
{
    size_t smallestIdx = _idx;
    size_t left = 2 * _idx + 1;
    size_t right = 2 * _idx + 2;

    
    if (left < _size && _arr[left] >= _arr[smallestIdx]) {
        smallestIdx = left;
    }

    
    if (right < _size && _arr[right] >= _arr[smallestIdx]) {
        smallestIdx = right;
    }

    
    if (smallestIdx != _idx) {
        std::swap(_arr[_idx], _arr[smallestIdx]);
        MinHeapify(_arr, _size, smallestIdx);
    }
}

void BuildMinHeap(std::vector<int>& _arr)
{
    //전체 사이즈의 반으로 나누면 부모 노드일 가능성이 있는 애들만 남음.
    for (size_t i = _arr.size() / 2; i != -1; --i)
    {
        MinHeapify(_arr, _arr.size(), i);
    }
}

void MinHeapSort(std::vector<int>& _arr)
{
    BuildMinHeap(_arr);

    for (size_t i = _arr.size() - 1; i > 0; --i)
    {
        std::swap(_arr[0], _arr[i]);
        MinHeapify(_arr, i, 0);
    }
}

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    std::vector<int> test = { 1, 1, 2, 2, 3, 2, 4, 5 };

    MinHeapSort(test);

    return 0;
}
