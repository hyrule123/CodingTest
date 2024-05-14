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
template <typename T>
struct stack {
    stack(size_t _capacity) : cont(_capacity), stackPos(-1) {}

    template <typename U>
    void Insert(const U& _t) { ++stackPos; cont[stackPos] = _t; }
    T* Back() { if (0 <= stackPos) { return &(cont[stackPos]); } return nullptr; };
    void Pop() { if (0 <= stackPos) { --stackPos; } }

    std::vector<T> cont;
    std::int64_t stackPos = -1;
};

struct command {
    enum e : int { Insert = 1, PrintBackAndPop, PrintSize, PrintIsEmpty, PrintBack };
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    stack<int> iStack(1000000);
    int N{}; std::cin >> N;

    for (int i = 0; i < N; ++i) {
        command::e com{};
        std::cin >> reinterpret_cast<int&>(com);

        switch (com)
        {
        case command::Insert: {
            int input{}; std::cin >> input;
            iStack.Insert(input);
            break;
        }
        case command::PrintBackAndPop: {
            int* elem = iStack.Back();
            if (elem) {
                std::cout << *elem << '\n';
            }
            else { 
                std::cout << -1 << '\n'; 
            }
            iStack.Pop();
            break;
        }
        case command::PrintSize: {
            std::cout << iStack.stackPos + 1 << '\n';
            break;
        }
        case command::PrintIsEmpty: {
            std::cout << (int)(-1 == iStack.stackPos ? 1 : 0) << '\n';
            break;
        }
        case command::PrintBack: {
            int* elem = iStack.Back();
            if (elem) {
                std::cout << *elem << '\n';
            }
            else { 
                std::cout << -1 << '\n'; 
            }
            break;
        }

        default:
            break;
        }
    }

    return 0;
}
