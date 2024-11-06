//Templatized HeapSort
#include <vector>
#include <type_traits>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b)
{
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};


template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void Heapify(std::vector<T>& _arr, const size_t _arrSize, const size_t _idx)
{
    size_t extremeIdx = _idx;
    size_t left = 2 * _idx + 1;
    size_t right = 2 * _idx + 2;

    if (left < _arrSize && CompareStruct::Compare(_arr[extremeIdx], _arr[left]))
    {
        extremeIdx = left;
    }

    if (right < _arrSize && CompareStruct::Compare(_arr[extremeIdx], _arr[right]))
    {
        extremeIdx = right;
    }

    if (extremeIdx != _idx)
    {
        std::swap(_arr[_idx], _arr[extremeIdx]);
        Heapify<CompareStruct, T>(_arr, _arrSize, extremeIdx);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void BuildHeap(std::vector<T>& _arr)
{
    const size_t arrSize = _arr.size();
    for (size_t i = _arr.size() / 2; i != -1; --i)
    {
        Heapify<CompareStruct, T>(_arr, arrSize, i);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void HeapSort(std::vector<T>& _arr)
{
    BuildHeap<CompareStruct, T>(_arr);

    for (size_t i = _arr.size() - 1; i > 0; --i)
    {
        std::swap(_arr[0], _arr[i]);
        Heapify<CompareStruct, T>(_arr, i, 0);
    }
}