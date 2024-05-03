#include <vector>
#include <type_traits>
#include <functional>

//concept, ���ø� ����//
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b)
{
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};

//���ϰ�: ���ĵ� pivot�� ��ġ
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
inline size_t Partition(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx)
{
    using compType = CompStruct::CompareType;

    //���� ó��
    if (_startIdx >= _endIdx)
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
    compType pivot = _vec[_endIdx];

    while (true)
    {
        //quick sort ����
        //<=�� ����: ���� ���ʿ� �ִ� pivot �ε����͵� �񱳸� �ؾߵ�
        while (start <= end && CompStruct::Compare(_vec[start], pivot))
        {
            ++start;
        }
        while (start < end && false == CompStruct::Compare(_vec[end], pivot))
        {
            --end;
        }
        //left, right �����Ͱ� �����ϸ� ���� �Ϸ�
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
size_t QuickSelect(std::vector<T>& _vec, size_t _idxToFind, size_t _startIdx, size_t _endIdx)
{
    using compType = CompStruct::CompareType;
    static_assert(std::is_same_v<T, compType>, "���Ϸ��� Ÿ�� ����ġ");

    //partition ȣ��, ���ĵ� �ǹ� �ε����� �޾ƿ´�.
    size_t pivotIdx = Partition<T, CompStruct>(_vec, _startIdx, _endIdx);

    if (-1 == pivotIdx)
    {
        return pivotIdx;
    }

    //ã�� �ε����� �ǹ� ����(���)
    if (_idxToFind < pivotIdx)
    {
        pivotIdx = QuickSelect<T, CompStruct>(_vec, _idxToFind, _startIdx, pivotIdx - 1);
    }

    //ã�� �ε����� �ǹ� ����(���)
    else if (pivotIdx < _idxToFind)
    {
        pivotIdx = QuickSelect<T, CompStruct>(_vec, _idxToFind, pivotIdx + 1, _endIdx);
    }

    //ã������� pivot�� ��ȯ�Ѵ�.
    return pivotIdx;
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSort(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx)
{
    using compType = CompStruct::CompareType;
    static_assert(std::is_same_v<T, compType>, "���Ϸ��� Ÿ�� ����ġ");

    //partition ȣ��, ���ĵ� �ǹ��� �ε����� �޾ƿ´�.
    size_t pivotIdx = Partition<T, CompStruct>(_vec, _startIdx, _endIdx);

    if (-1 == pivotIdx)
    {
        return;
    }

    if (0 < pivotIdx)
    {
        QuickSort<T, CompStruct>(_vec, _startIdx, pivotIdx - 1);
    }
    if (pivotIdx < _vec.size())
    {
        QuickSort<T, CompStruct>(_vec, pivotIdx + 1, _endIdx);
    }
}