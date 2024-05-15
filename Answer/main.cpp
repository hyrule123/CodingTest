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
struct CircleQueue {
    CircleQueue(size_t _capacity) : front(), end(), capacity(_capacity) { 
        cont.resize(_capacity + 1); 
    }

    inline size_t NextCursor(size_t _cursor) { if ((++_cursor) >= cont.size()) { _cursor = 0; } return _cursor; }
    inline bool Empty() { return (front == end); }
    inline bool Full() { return (front == NextCursor(end)); }

    inline void PushBack(int _i) { 
        size_t nextEnd = NextCursor(end); 
        if (front != nextEnd) {
            cont[end] = _i; end = nextEnd;
        }
    }
    inline int Front() { return cont[front]; }
    inline void Pop() { if (false == Empty()) { front = NextCursor(front); } }

    std::vector<int> cont;
    size_t front;
    size_t end;
    size_t capacity;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; int K{}; std::cin >> N >> K;
    //K번째 사람을 꺼내와야 하므로 K-1번째까지만 반복하기 위함
    --K;

    CircleQueue josephus{ (size_t)N };
    for (int i = 0; i < N; ++i) {
        josephus.PushBack(i + 1);
    }

    std::cout << '<';
    while (false == josephus.Empty()) {
        for (int i = 0; i < K; ++i) {
            int front = josephus.Front();
            josephus.Pop();
            josephus.PushBack(front);
        }
        
        int front = josephus.Front();
        josephus.Pop();
        std::cout << front << ", ";
    }
    std::cout.seekp(-2, std::ios::end);
    std::cout << '>';

    return 0;
}
