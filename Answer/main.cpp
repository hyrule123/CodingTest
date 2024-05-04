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
        //번갈아가면서 비교하고, 조건에 부합해서 값을 넣었을 경우 인덱스를 한단계씩 올려준다.
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

    //분할 갯수가 불균형하여 한 쪽이 남아있을 수도 있음 -> 남아있는 값들을 복사해준다.
    for (; lIter <= mid; ++lIter) {
        _temp[writeIter] = _orig[lIter];
        ++writeIter;
    }
    for (; rIter <= _end; ++rIter) {
        _temp[writeIter] = _orig[rIter];
        ++writeIter;
    }

    //_temp에 정렬되어있는 데이터를 가져온다.
    std::copy(_temp.begin() + _start, _temp.begin() + _end + 1, _orig.begin() + _start);
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void MergeSortAndRemoveRedundant(std::vector<T>& _vec) {
    std::vector<T> temp{};
    temp.resize(_vec.size());

    DivideAndConquerRecursive<CompareStruct, T>(_vec, temp, 0, temp.size() - 1);

    //temp 벡터 만든 김에 이거 써서 중복값 제거하자
    temp.clear();
    temp.push_back(_vec[0]);

    for (size_t i = 1; i < _vec.size(); ++i) {
        if (_vec[i - 1] == _vec[i]) {
            continue;
        }

        temp.push_back(_vec[i]);
    }

    _vec.swap(temp);
}

//Param: 정렬된 배열, 찾고자하는 값
//값을 찾으면 cout
inline void BinarySearchAndPrint(std::vector<int>& _sorted, int _value)
{
    size_t startIdx = 0;
    size_t endIdx = _sorted.size();
    size_t midIdx{};

    while (true)
    {
        midIdx = (startIdx + endIdx) / 2;
        //왼쪽
        if (_value < _sorted[midIdx]) {
            endIdx = midIdx;
        }
        //오른쪽
        else if (_sorted[midIdx] < _value) {
            startIdx = midIdx + 1;
        }
        else
        {
            std::cout << midIdx << ' ';
            return;
        }
    }
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{};
    std::cin >> N;
    std::vector<int> origArr{};
    std::vector<int> sorted{};
    origArr.resize(N);
    sorted.resize(N);

    for (size_t i = 0; i < N; ++i) {
        std::cin >> origArr[i];
    }
    memcpy(sorted.data(), origArr.data(), origArr.size() * sizeof(int));

    struct IntAscending {
        using Type = int;
        static inline bool Compare(Type _a, Type _b) {
            return _a <= _b;
        }
    };

    //Sort 실행 및 중복값 제거
    //중복값을 제거하면 인덱스 번호 = 각 숫자별 랭킹이 됨
    MergeSortAndRemoveRedundant<IntAscending>(sorted);

    //각 원소들을 이진탐색을 통해 순서 확인
    for (size_t i = 0; i < origArr.size(); ++i) {
        BinarySearchAndPrint(sorted, origArr[i]);
    }

    return 0;
}
