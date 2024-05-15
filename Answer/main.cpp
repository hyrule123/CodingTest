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
//규칙: frontCursor은 endCursor 위치까지 이동가능.
//endCursor은 frontCursor 하나 전까지만 이동가능.()
//실제 capacity == cont.size() - 1
struct CircleQueue {
    CircleQueue(size_t _size) : cont(_size + 1), frontCursor(0), endCursor(0), queueCapacity(_size) {}

    inline size_t NextCursor(size_t _cursor) { if ((++_cursor) == cont.size()) { _cursor = 0; } return _cursor; }
    inline bool Empty() { return (frontCursor == endCursor); }
    inline bool Full() { return frontCursor == NextCursor(endCursor); }
    inline size_t Size() { return (endCursor + (frontCursor > endCursor ? queueCapacity : 0) - frontCursor); }

    inline void Insert(int _i) {
        size_t nextEnd = NextCursor(endCursor);
        if (frontCursor != nextEnd) //if full 
        {
            cont[endCursor] = _i; endCursor = nextEnd; 
        }
    }

    inline void Pop() { if (false == Empty()) { frontCursor = NextCursor(frontCursor); } }
    inline int Front() { return cont[frontCursor]; }

    std::vector<int> cont;
    size_t frontCursor;
    size_t endCursor;
    size_t queueCapacity;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;

    CircleQueue cq((size_t)N);
    for (int i = 1; i <= N; ++i) {
        cq.Insert(i);
    }
    
    int last = cq.Front();
    while (true) {
        cq.Pop();

        if (cq.Empty()) {
            break;
        }

        last = cq.Front();
        cq.Insert(last);
        cq.Pop();
    }

    std::cout << last;

    return 0;
}
