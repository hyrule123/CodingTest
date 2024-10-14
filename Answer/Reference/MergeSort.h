//Templatized MergeSort//
#include <vector>
#include <type_traits>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b) {
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void DivideAndConquerRecursive(std::vector<T>& _orig, std::vector<T>& _temp, const size_t _start, const size_t _end) {
    if (false == (_start < _end)) {
        return;
    }

    const size_t mid = (_start + _end) / 2;

    //Divide, Conquer
    DivideAndConquerRecursive<CompareStruct, T>(_orig, _temp, _start, mid);
    DivideAndConquerRecursive<CompareStruct, T>(_orig, _temp, mid + 1, _end);

    size_t lIter = _start;
    size_t rIter = mid + 1;
    size_t writeIter = lIter;

    //Merge
    while (lIter <= mid && rIter <= _end) {
        if (CompareStruct::Compare(_orig[lIter], _orig[rIter])) {
            _temp[writeIter] = _orig[lIter];
            ++lIter;
            ++writeIter;
        }
        else {
            _temp[writeIter] = _orig[rIter];
            ++rIter;
            ++writeIter;
        }
    }

    for (; lIter <= mid; ++lIter) {
        _temp[writeIter] = _orig[lIter];
        ++writeIter;
    }
    for (; rIter <= _end; ++rIter) {
        _temp[writeIter] = _orig[rIter];
        ++writeIter;
    }

    std::copy(_temp.begin() + _start, _temp.begin() + _end + 1, _orig.begin() + _start);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void MergeSort(std::vector<T>& _vec) {
    std::vector<T> temp{};
    temp.resize(_vec.size());

    DivideAndConquerRecursive<CompareStruct, T>(_vec, temp, 0, temp.size() - 1);
}