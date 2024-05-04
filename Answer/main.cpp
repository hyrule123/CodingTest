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

#include <string>
#include <array>

//Templatized MergeSort//
#include <vector>
#include <type_traits>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b) {
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void DivideAndConquerRecursive(std::vector<T>& _orig, std::vector<T>& _temp, const size_t _start, const size_t _end) {
    const size_t size = _end - _start + 1;
    if (size <= 1) {
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
void MergeSort(std::vector<T>& _vec) {
    std::vector<T> temp{};
    temp.resize(_vec.size());

    DivideAndConquerRecursive<CompareStruct, T>(_vec, temp, 0, temp.size() - 1);
}

//정렬의 대상이 되는 구조체는 string_view만 들고있어준다.
struct  MemberInfo {
    std::int64_t Age;
    std::string_view Name;
};


int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    struct MemberInfoAscending {
        using Type = MemberInfo;
        static inline bool Compare(const Type& _a, const Type& _b) {
            return _a.Age <= _b.Age;
        }
    };

    std::size_t N{};
    std::cin >> N;

    std::vector<MemberInfo> members{};
    members.resize(N);

    //실제 이름은 별도의 배열에 보관(비교 대상이 아니므로 따로 보관해도 상관 없음)
    std::vector<std::array<char, 128>> arrNames{};
    arrNames.resize(N);
    
    for (size_t i = 0; i < members.size(); ++i) {
        std::cin >> members[i].Age;
        std::cin.get();
        std::cin.getline(arrNames[i].data(), arrNames[i].size());
        members[i].Name = arrNames[i].data();
    }

    //참고: Merge sort는 stable sort이므로 정렬 전의 상대 순서가 유지된다는 특성이 있다.
    //* Heap sort는 stable sort가 아니기에 유지되지 않음.
    MergeSort<MemberInfoAscending>(members);

    for (size_t i = 0; i < members.size(); ++i) {
        std::cout << members[i].Age << ' ' << members[i].Name << '\n';
    }

    return 0;
}
