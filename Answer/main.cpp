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

struct balloon {
    int idx;
    int moveDist;
};

struct deque {
    deque(size_t _capacity) : cont(), capacity(_capacity), size(), begin(), end() { cont.resize(capacity + 1); }

    size_t PrevCursor(size_t _cursor) { if (_cursor == 0) { _cursor = cont.size(); } return --_cursor; }
    size_t NextCursor(size_t _cursor) { if (++_cursor == cont.size()) { _cursor = 0; } return _cursor; }
    bool Empty() { return (size == 0); }
    bool Full() { return (size == capacity); }

    size_t Size() { return size; }

    void PushFront(balloon _b) {
        if (Full()) { return; }

        begin = PrevCursor(begin);
        cont[begin] = _b;
        ++size;
    }
    void PushBack(balloon _b) {
        if (Full()) { return; }

        cont[end] = _b;
        end = NextCursor(end);
        ++size;
    }
    void PopFront() {
        if (false == Empty()) {
            begin = NextCursor(begin);
            --size;
        }
    }
    void PopBack() {
        if (false == Empty()) {
            end = PrevCursor(end);
            --size;
        }
    }
    balloon Front() { return cont[begin]; }
    balloon Back() { return cont[PrevCursor(end)]; }

    std::vector<balloon> cont;
    size_t capacity;
    size_t size;
    size_t begin;
    size_t end;
};


int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;
    deque dq{ (size_t)N };

    for (int i = 1; i <= N; ++i) {
        int input{}; std::cin >> input;
        dq.PushBack(balloon{ i, input });
    }

    balloon move = dq.Front();
    dq.PopFront();
    std::cout << 1 << ' ';
    for (int i = 1; i < N; ++i) {
        if (move.moveDist > 0) {
            --move.moveDist;
            for (int i = 0; i < move.moveDist; ++i) {
                balloon temp = dq.Front();
                dq.PopFront();
                dq.PushBack(temp);
            }
            move = dq.Front();
            std::cout << move.idx << ' ';
            dq.PopFront();
        }
        else {
            ++move.moveDist;
            for (int i = move.moveDist; i < 0; ++i) {
                balloon temp = dq.Back();
                dq.PopBack();
                dq.PushFront(temp);
            }
            move = dq.Back();
            std::cout << move.idx << ' ';
            dq.PopBack();
        }
    }
    return 0;
}
