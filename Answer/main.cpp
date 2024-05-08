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

#include <vector>
#include <set>
#include <compare>
#include <string_view>
#include <algorithm>

struct Str {
    constexpr static const size_t s_maxLength = 21;
    char s[s_maxLength];
    int length;

    inline bool operator == (const Str& _other) const {
        if (this->length != _other.length) {
            return false;
        }

        for (int i = 0; i < length; ++i) {
            if (this->s[i] != _other.s[i]) {
                return false;
            }
        }

        return true;
    }

    //사전순 정렬 Spaceship operator
    inline std::strong_ordering operator <=> (const Str& _other) const {
        int size = std::min(length, _other.length);
        
        for (int i = 0; i < size; ++i) {
            if (this->s[i] == _other.s[i]) {
                continue;
            }

            return (this->s[i] <=> _other.s[i]);
        }

        return this->length <=> _other.length;
    }
};

//처음에는 이진탐색트리에 전부 삽입해서 정렬된 상태를 만들고, 한번에 출력하는 건줄 알았는데, 그게 아닌듯...
//문제는 듣보의 '보'(M으로 들어오는 애들)이 정렬되어 있는지 모른다는것임...
//결국 전부 받아서 검사해 본 뒤에야 순서를 결정할 수 있기 때문에 '듣'을 unordered_map에 넣고, '보'와 공통된 친구들을 따로 빼놓은 뒤, 정렬을 돌려야 함...
int main() {
    USING_IOSTREAM;
    READ_INPUT;
    WRITE_OUTPUT;

    int N{}, M{};
    std::cin >> N >> M;

    std::set<Str, std::less<Str>> D{};  

    Str input{};
    std::cin.getline(input.s, input.s_maxLength);
    for (int i = 0; i < N; ++i) {
        input.s[0] = '\0';
        input.length = 0;

        std::cin.getline(input.s, input.s_maxLength);
        input.length = (int)std::strlen(input.s);

        D.insert(input);
    }

    std::vector<std::string_view> DBJ{};
    DBJ.reserve(N);

    for (int i = 0; i < M; ++i) {
        input.s[0] = '\0';
        input.length = 0;

        std::cin.getline(input.s, input.s_maxLength);
        input.length = (int)std::strlen(input.s);

        auto iter = D.find(input);
        if (iter != D.end()) {
            DBJ.push_back(std::string_view(iter->s, iter->length));
        }
    }

    std::sort(DBJ.begin(), DBJ.end());

    std::cout << DBJ.size() << '\n';
    for (size_t i = 0; i < DBJ.size(); ++i) {
        std::cout << DBJ[i] << '\n';
    }

    return 0;
}
