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
struct queue
{
    queue(size_t _size) : queuePos() { cont.reserve(_size); }

    inline bool empty() { return (queuePos == cont.size()); }
    inline size_t size() { return (cont.size() - queuePos); }
    inline void push(int _i) { cont.push_back(_i); };
    inline void pop() { if (false == empty()) { ++queuePos; } }
    
    inline int front() { return cont[queuePos]; }
    inline int back() { return cont.back(); }

    std::vector<int> cont;
    size_t queuePos;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;
    queue q((size_t)N);

    std::string command{};
    for (int i = 0; i < N; ++i) {
        command.clear();
        std::cin >> command;

        constexpr const std::string_view commands[] = { "push", "pop", "size", "empty", "front", "back" };
        if (command == commands[0]) {
            int input{}; std::cin >> input;
            q.push(input);
        }
        else if (command == commands[1]) {
            if (q.empty()) {
                std::cout << -1 << '\n';
            }
            else {
                std::cout << q.front() << '\n';
                q.pop();
            }
        }
        else if (command == commands[2]) {
            std::cout << q.size() << '\n';
        }
        else if (command == commands[3]) {
            std::cout << (int)q.empty() << '\n';
        }
        else if (command == commands[4]) {
            if (q.empty()) {
                std::cout << -1 << '\n';
            }
            else {
                std::cout << q.front() << '\n';
            }
        }
        else if (command == commands[5]) {
            if (q.empty()) {
                std::cout << -1 << '\n';
            }
            else {
                std::cout << q.back() << '\n';
            }
        }
    }

    return 0;
}
