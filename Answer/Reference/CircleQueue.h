#include <vector>
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