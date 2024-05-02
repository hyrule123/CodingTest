﻿#ifndef LOCAL
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
#include <functional>

//concept, 템플릿 연습//
template <typename T>
concept is_comparable = requires(T::CompareType && _a, T::CompareType && _b)
{
    { T::Compare(_a, _b) } -> std::same_as<bool>;
};

//리턴값: 정렬된 pivot의 위치
template<typename T, typename CompStruct> requires is_comparable<CompStruct>
inline size_t Partition(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx)
{
    using compType = CompStruct::CompareType;

    //예외 처리
    if (_startIdx >= _endIdx)
    {
        return _startIdx;
    }

    const size_t size = _endIdx - _startIdx + 1;
    if (size == 1)
    {
        return _startIdx;
    }
    else if (size == 2)
    {
        //똑같이 맨 우측값을 pivot이라고 가정하고 진행.
        //pivot이 왼쪽에 들어가면 start 반환, 오른쪽에 들어가면 end 반환
        if (false == CompStruct::Compare(_vec[_startIdx], _vec[_endIdx]))
        {
            std::swap(_vec[_startIdx], _vec[_endIdx]);
            return _startIdx;
        }
        else
        {
            return _endIdx;
        }
    }
    //////////////////////////////////

    size_t start = _startIdx;
    size_t end = _endIdx - 1;
    std::swap(_vec[end], _vec[_endIdx]);
    compType pivot = _vec[_endIdx];

    while (true)
    {
        //quick sort 진행
        //<=인 이유: 가장 뒤쪽에 있는 pivot 인덱스와도 비교를 해야됨
        while (start <= end && CompStruct::Compare(_vec[start], pivot))
        {
            ++start;
        }
        while (start < end && false == CompStruct::Compare(_vec[end], pivot))
        {
            --end;
        }
        //left, right 포인터가 교차하면 정렬 완료
        if (start >= end)
        {
            std::swap(_vec[start], _vec[_endIdx]);
            break;
        }

        std::swap(_vec[start], _vec[end]);
    }

    return start;
}

template<typename T, typename CompStruct> requires is_comparable<CompStruct>
size_t QuickSelect(std::vector<T>& _vec, size_t _idxToFind, size_t _startIdx, size_t _endIdx)
{
    using compType = CompStruct::CompareType;
    static_assert(std::is_same_v<T, compType>, "비교하려는 타입 불일치");

    //partition 호출, 정렬된 피벗 인덱스를 받아온다.
    size_t pivotIdx = Partition<T, CompStruct>(_vec, _startIdx, _endIdx);

    //찾을 인덱스가 피벗 좌측(재귀)
    if (_idxToFind < pivotIdx)
    {
        pivotIdx = QuickSelect<T, CompStruct>(_vec, _idxToFind, _startIdx, pivotIdx - 1);
    }

    //찾을 인덱스가 피벗 우측(재귀)
    else if (pivotIdx < _idxToFind)
    {
        pivotIdx = QuickSelect<T, CompStruct>(_vec, _idxToFind, pivotIdx + 1, _endIdx);
    }

    //찾았을경우 pivot을 반환한다.
    return pivotIdx;
}


int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}, k{};
    std::cin >> N >> k;

    std::vector<unsigned int> scores{};
    scores.resize(N);
    for (size_t i = 0; i < scores.size(); ++i)
    {
        std::cin >> scores[i];
    }

    //template에 전달할 구조체
    struct Compare_uint
    {
        using CompareType = unsigned int;
        inline static bool Compare(const CompareType& _l, const CompareType& _r)
        {
            return _l >= _r;
        }
    };

    QuickSelect<unsigned int, Compare_uint>(scores, k - 1, 0, scores.size() - 1);
    std::cout << scores[k - 1];

    return 0;
}
