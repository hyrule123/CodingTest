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
struct stack {
    stack() { Reset(); }

    inline bool NotEmpty() { return (0 <= stackPos); }
    inline void Insert(char _c) { ++stackPos; cont[stackPos] = _c; }
    inline char* Back() { if (NotEmpty()) { return &(cont[stackPos]); } return nullptr; }
    inline void Pop() { if (NotEmpty()) { --stackPos; }; }
    inline void Reset() { cont.resize(104, '\0'); stackPos = -1; }

    std::vector<char> cont;
    int stackPos;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    
    char str[104]{};
    stack pairs{};
    while(true) {
        str[0] = '\0';
        std::cin.getline(str, 104);
        if (str[0] == '.') { break; }

        pairs.Reset();

        bool isValid = true;
        for (int i = 0; i < 104 && str[i] != '.'; ++i) {

            if (str[i] == '(') {
                pairs.Insert('(');
            }
            else if (str[i] == ')') {
                char* back = pairs.Back();
                if (nullptr == back || '(' != *back) {
                    isValid = false;
                    break;
                }
                else {
                    pairs.Pop();
                }
            }
            else if (str[i] == '[') {
                pairs.Insert('[');
            }
            else if (str[i] == ']') {
                char* back = pairs.Back();
                if (nullptr == back || '[' != *back) {
                    isValid = false;
                    break;
                }
                else {
                    pairs.Pop();
                }
            }
        }

        constexpr const std::string_view yes = "yes\n";
        constexpr const std::string_view no = "no\n";
        if (isValid) {
            if (pairs.NotEmpty()) {
                std::cout << no;
            }
            //스택이 정리되었을 경우 yes
            else {
                std::cout << yes;
            }
        }
        else {
            std::cout << no;
        }
    }

    return 0;
}
