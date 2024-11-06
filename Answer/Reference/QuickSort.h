//Templatized QuickSort, QuickSelect
#include <vector>
#include <type_traits>
#include <random>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b) {
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
inline size_t Partition(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx) {
    size_t start = _startIdx;
    size_t end = _endIdx - 1;
    T& pivot = _vec[_endIdx];

    while (true) {
        //quick sort
        while (start <= end && CompareStruct::Compare(_vec[start], pivot)) {
            ++start;
        }
        while (start < end && false == CompareStruct::Compare(_vec[end], pivot)) {
            --end;
        }
        if (start >= end) {
            std::swap(_vec[start], pivot);
            break;
        }

        std::swap(_vec[start], _vec[end]);
    }


    return start;
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
inline size_t Partition_Random(std::vector<T>& _vec, const size_t _startIdx, const size_t _endIdx) {
    size_t randomIdx = _startIdx + (rand() % (_endIdx - _startIdx));

    std::swap(_vec[_endIdx], _vec[randomIdx]);

    return Partition<CompareStruct, T>(_vec, _startIdx, _endIdx);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSelectRecursive(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx, size_t _idxToFind) {
    if (_startIdx < _endIdx) {
        size_t pivotIdx = Partition_Random<CompareStruct, T>(_vec, _startIdx, _endIdx);

        if (_idxToFind < pivotIdx) {
            QuickSelectRecursive<CompareStruct, T>(_vec, _startIdx, pivotIdx, _idxToFind);
        }

        else if (pivotIdx < _idxToFind) {
            QuickSelectRecursive<CompareStruct, T>(_vec, pivotIdx + 1, _endIdx, _idxToFind);
        }
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSelect(std::vector<T>& _vec, size_t _idxToFind) {
    QuickSelectRecursive<CompareStruct, T>(_vec, 0, _vec.size() - 1, _idxToFind);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSort(std::vector<T>& _vec, size_t _startIdx, size_t _endIdx) {
    if (_startIdx < _endIdx) {
        size_t pivotIdx = Partition_Random<CompareStruct, T>(_vec, _startIdx, _endIdx);

        QuickSort<CompareStruct, T>(_vec, _startIdx, pivotIdx);
        QuickSort<CompareStruct, T>(_vec, pivotIdx + 1, _endIdx);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void QuickSort(std::vector<T>& _vec) {
    QuickSort<CompareStruct, T>(_vec, 0, _vec.size() - 1);
}