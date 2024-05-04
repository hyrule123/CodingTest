//Templatized QuickSort, QuickSelect
#include <vector>
#include <type_traits>
#include <random>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b)
{
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};
//리턴값: 정렬된 pivot의 위치
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
inline size_t Partition(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx)
{
    size_t start = _startIdx;
    size_t end = _endIdx - 1;
    T& pivot = _vec[_endIdx];

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
        //left, right 포인터가 교차할 때 start 위치가 pivot값이 들어갈 자리이다.
        if (start >= end)
        {
            std::swap(_vec[start], pivot);
            break;
        }

        //서로 교차하지 않았을 경우 start와 end에 있는 값을 교환해준다.
        std::swap(_vec[start], _vec[end]);
    }


    return start;
}

//범위 안의 랜덤한 인덱스를 인덱스의 끝으로 보냄(Pivot 역할)
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
inline size_t Partition_Random(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx)
{
    //나오는 범위: _start ~ _end
    size_t randomIdx = _startIdx + (rand() % (_endIdx - _startIdx));

    //나온 랜덤 인덱스 번호의 값을 끝으로 보낸다(Pivot으로 설정)
    std::swap(_vec[_endIdx], _vec[randomIdx]);

    return Partition<CompareStruct, T>(_vec, _startIdx, _endIdx);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSelectRecursive(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx, size_t _idxToFind)
{
    if (_startIdx < _endIdx)
    {
        //partition 호출, 정렬된 피벗 인덱스를 받아온다.
        size_t pivotIdx = Partition_Random<CompareStruct, T>(_vec, _startIdx, _endIdx);

        //찾을 인덱스가 피벗 좌측(재귀)
        if (_idxToFind < pivotIdx)
        {
            QuickSelectRecursive<CompareStruct, T>(_vec, _startIdx, pivotIdx, _idxToFind);
        }

        //찾을 인덱스가 피벗 우측(재귀)
        else if (pivotIdx < _idxToFind)
        {
            QuickSelectRecursive<CompareStruct, T>(_vec, pivotIdx + 1, _endIdx, _idxToFind);
        }
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSelect(std::vector<T>& _vec, size_t _idxToFind)
{
    QuickSelectRecursive<CompareStruct, T>(_vec, 0, _vec.size() - 1, _idxToFind);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSort(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx)
{
    if (_startIdx < _endIdx)
    {
        //partition 호출, 정렬된 피벗의 인덱스를 받아온다.
        size_t pivotIdx = Partition_Random<CompareStruct, T>(_vec, _startIdx, _endIdx);

        QuickSort<CompareStruct, T>(_vec, _startIdx, pivotIdx);
        QuickSort<CompareStruct, T>(_vec, pivotIdx + 1, _endIdx);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSort(std::vector<T>& _vec)
{
    QuickSort<CompareStruct, T>(_vec, 0, _vec.size() - 1);
}