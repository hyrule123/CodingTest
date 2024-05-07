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
void MergeSort(std::vector<T>& _vec) {
    if (2 > _vec.size()) {
        return;
    }

    std::vector<T> temp{};
    temp.resize(_vec.size());
    DivideAndConquerRecursive<CompareStruct, T>(_vec, temp, 0, temp.size() - 1);
}

//Endianness 생각하면 memcpy나 union보단 비트연산자가 나을듯
inline std::uint64_t NameToUint64(const std::string_view _name) {
    std::uint64_t ret{};

    if (false == _name.empty()) {
        for (size_t i = 0; i < _name.size(); ++i) {
            ret += (static_cast<std::uint64_t>(_name[i]) << (4 - i) * 8);
        }
    }

    return ret;
}

inline std::array<char, 6> Uint64ToName(const std::uint64_t _name) {
    std::array<char, 6> ret{};
    int cursor = 0;
    for (int i = 4; i >= 0; --i) {
        char c = static_cast<char>(_name >> i * 8 & 0xff);
        if ('\0' != c) {
            ret[cursor] = c;
            ++cursor;
        }
    }
    ret[cursor] = '\0';
    return ret;
}

struct Attendance {
    //이름의 최대 길이는 5->uint64_t로 변환
    std::uint64_t NameNum;
    bool IsEnter;
};
struct AttendanceCompare {
    using Type = Attendance;
    inline static bool Compare(const Type& _a, const Type& _b) {
        return _a.NameNum >= _b.NameNum;
    }
};


//로직
//이름은 5글자 이하라고 했으므로 -> uint64 형태로 변환 가능. "ABC" == 0x00,00,00,'A','B','C',00,00
//cf)자릿수 유지를 해줘야 사전순 비교 가능
//MergeSort는 stable sort이므로 정렬을 진행해도 상대적 위치가 그대로임.(시간순 정렬이 깨지지 않음)
//->MergeSort를 통해서 정렬 후 마지막 기록이 "enter"인 사람만 출력한다.
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{};
    std::cin >> N;

    std::vector<Attendance> attendLog{};
    attendLog.resize(N);

    {
        constexpr const std::string_view enterMsg = "enter";
        std::string name{};
        std::string attend{};
        for (size_t i = 0; i < N; ++i) {
            std::cin >> name >> attend;

            attendLog[i].NameNum = NameToUint64(name);
            attendLog[i].IsEnter = (enterMsg == attend);
        }
    }

    MergeSort<AttendanceCompare>(attendLog);

    if (attendLog.empty()) {
        return 0;
    }
    else if (attendLog.size() == 1) {
        std::cout << Uint64ToName(attendLog[0].NameNum).data() << '\n';
    }
    else {
        const size_t end = N - 1;
        for (size_t i = 0; i < end; ++i) {
            if (attendLog[i].NameNum != attendLog[i + 1].NameNum && attendLog[i].IsEnter) {
                std::cout << Uint64ToName(attendLog[i].NameNum).data() << '\n';
            }
        }

        //마지막 인덱스 별도 처리(비교할 다음 인덱스가 없으므로)
        if (attendLog[end].IsEnter) {
            std::cout << Uint64ToName(attendLog[end].NameNum).data() << '\n';
        }
    }

    return 0;
}
