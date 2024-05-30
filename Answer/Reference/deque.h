#include <vector>
struct deque {
    deque(size_t _capacity) : cont(), capacity(_capacity), size(), begin(), end() { cont.resize(capacity + 1); }

    size_t PrevCursor(size_t _cursor) { if (_cursor == 0) { _cursor = cont.size(); } return --_cursor; }
    size_t NextCursor(size_t _cursor) { if (++_cursor == cont.size()) { _cursor = 0; } return _cursor; }
    bool Empty() { return (size == 0); }
    bool Full() { return (size == capacity); }

    size_t Size() { return size; }

    void PushFront(unsigned int _b) {
        if (Full()) { return; }

        begin = PrevCursor(begin);
        cont[begin] = _b;
        ++size;
    }
    void PushBack(unsigned int _b) {
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
    unsigned int Front() { return cont[begin]; }
    unsigned int Back() { return cont[PrevCursor(end)]; }
    
    std::vector<unsigned int> cont;
    size_t capacity;
    size_t size;
    size_t begin;
    size_t end;
};