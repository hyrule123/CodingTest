//Templatized QuickSort, QuickSelect
#include <vector>
#include <type_traits>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b)
{
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};
//리턴값: 정렬된 pivot의 위치
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
inline size_t Partition(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx)
{
    //예외 처리
    if (_startIdx > _endIdx)
    {
        return -1;
    }

    const size_t size = _endIdx - _startIdx + 1;
    if (size == 1)
    {
        return _startIdx;
    }
    //////////////////////////////////

    size_t start = _startIdx;
    size_t end = _endIdx - 1;
    std::swap(_vec[end], _vec[_endIdx]);
    T pivot = _vec[_endIdx];

    while (true)
    {
        //quick sort 진행
        //<=인 이유: 가장 뒤쪽에 있는 pivot 인덱스와도 비교를 해야됨
        while (start <= end && CompareStruct::Compare(_vec[start], pivot))
        {
            ++start;
        }
        while (start < end && false == CompareStruct::Compare(_vec[end], pivot))
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

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSelectRecursive(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx, size_t _idxToFind)
{
    //partition 호출, 정렬된 피벗 인덱스를 받아온다.
    size_t pivotIdx = Partition<CompareStruct, T>(_vec, _startIdx, _endIdx);

    if (-1 == pivotIdx)
    {
        return;
    }

    //찾을 인덱스가 피벗 좌측(재귀)
    if (_idxToFind < pivotIdx)
    {
        QuickSelectRecursive<CompareStruct, T>(_vec, _startIdx, pivotIdx - 1, _idxToFind);
    }

    //찾을 인덱스가 피벗 우측(재귀)
    else if (pivotIdx < _idxToFind)
    {
        QuickSelectRecursive<CompareStruct, T>(_vec, pivotIdx + 1, _endIdx, _idxToFind);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSelect(std::vector<T>& _vec, size_t _idxToFind)
{
    QuickSelectRecursive<CompareStruct, T>(_vec, 0, _vec.size() - 1, _idxToFind);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSortRecursive(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx)
{
    //partition 호출, 정렬된 피벗의 인덱스를 받아온다.
    size_t pivotIdx = Partition<CompareStruct, T>(_vec, _startIdx, _endIdx);

    if (-1 == pivotIdx)
    {
        return;
    }

    if (0 < pivotIdx)
    {
        QuickSortRecursive<CompareStruct, T>(_vec, _startIdx, pivotIdx - 1);
    }
    if (pivotIdx < _vec.size())
    {
        QuickSortRecursive<CompareStruct, T>(_vec, pivotIdx + 1, _endIdx);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSort(std::vector<T>& _vec)
{
    QuickSortRecursive<CompareStruct, T>(_vec, 0, _vec.size() - 1);
}