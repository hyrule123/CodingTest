#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

////////////////////////////
#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
////////////////////////////

#include <vector>
#include <string_view>
struct VPS_Checker {
    VPS_Checker() : left_P_Count(0) {}

    inline bool Add(const char _c) { 
        if (_c == '(') { ++left_P_Count; } 
        else if (_c == ')') { --left_P_Count; }
        return (0 <= left_P_Count);
    }
    inline bool FinalCheck() { return 0 == left_P_Count; }

    int left_P_Count;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t T{}; std::cin >> T;

    
    char str[51]{};
    std::cin.getline(str, 51);
    for (size_t i = 0; i < T; ++i) {
        str[0] = '\0';

        VPS_Checker checker{};
        std::cin >> str;

        bool isValid = true;
        constexpr const std::string_view yes = "YES\n";
        constexpr const std::string_view no = "NO\n";
        for (int i = 0; i < 51; ++i) {
            if (str[i] == '\0') { break; }

            if (false == checker.Add(str[i])) {
                isValid = false;
                std::cout << no;
                break;
            }
        }

        if (isValid) {
            if (checker.FinalCheck()) {
                std::cout << yes;
            }
            else {
                std::cout << no;
            }
        }
    }

    return 0;
}
