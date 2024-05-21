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

int recursion(const char* s, int l, int r, int& callCount) {
    ++callCount;
    if (l >= r) return 1;
    else if (s[l] != s[r]) return 0;
    else return recursion(s, l + 1, r - 1, callCount);
}

int isPalindrome(const char* s, int& callCount) {
    return recursion(s, 0, (int)strlen(s) - 1, callCount);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;
    
    int T{}; std::cin >> T;

    char input[1004]{};
    for (int i = 0; i < T; ++i) {
        input[0] = '\0';
        std::cin >> input;
        int callCount = 0;
        int ispal = isPalindrome(input, callCount);
        std::cout << ispal << ' ' << callCount << '\n';
    }

    return 0;
}
