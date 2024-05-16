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
struct Deque {
    Deque(size_t _cap) : cont(_cap + 1), front(), rear(), size(), capacity(_cap) {}

    bool Empty() { return (size == 0); }
    bool Full() { return (size == capacity); }
    size_t Size() { return size; }

    void Resize(size_t _cap) {
        capacity = _cap;
        std::vector<int> temp(capacity + 1);

        size_t prevSize = size;
        for (int i = 0; false == Empty(); ++i) {
            temp[i] = Front();
            PopFront();
        }

        cont.swap(temp);
        front = 0;
        rear = prevSize;
        size = prevSize;
    }

    size_t NextCursor(size_t _cur) { if (++_cur == cont.size()) { _cur = 0; } return _cur; }
    size_t PrevCursor(size_t _cur) { if (_cur == 0) { _cur = cont.size(); } return --_cur; }
    
    void PushFront(int _i) {
        if (Full()) { return; }

        front = PrevCursor(front);
        cont[front] = _i;
        ++size;
    }
    void PushBack(int _i) {
        if (Full()) { return; }

        cont[rear] = _i;
        rear = NextCursor(rear);
        ++size;
    }
    void PopFront() {
        if (false == Empty()) {
            front = NextCursor(front);
            --size;
        }
    }
    void PopBack() {
        if (false == Empty()) {
            rear = PrevCursor(rear);
            --size;
        }
    }

    int Front() { return cont[front]; }
    int Back() { return cont[PrevCursor(rear)]; }

    std::vector<int> cont;
    size_t front;
    size_t rear;
    size_t size;
    size_t capacity;
};

//deque를 활용하면 풀수 있다.
//stack자료구조 뭐시기 데이터는 쓸모 없음
int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;

    std::vector<int> isStackElem((size_t)N);
    size_t queueSize{};
    
    //Input Line 2
    for (int i = 0; i < N; ++i) {
        std::cin >> isStackElem[i];
        if (false == isStackElem[i]) {
            ++queueSize;
        }
    }
    Deque dq(queueSize);

    //Input Line 3
    for (int i = 0; i < N; ++i) {
        int input{}; std::cin >> input;
        if (false == isStackElem[i]) {
            //3번줄의 입력은 입력 순서대로 앞에서부터 채워준다.(1 4)
            dq.PushBack(input);
        }
    }

    //Input Line 4
    int M{}; std::cin >> M;
    dq.Resize(queueSize + M);
    for (int i = 0; i < M; ++i) {
        int input{}; std::cin >> input;
        //Input Line 5, 앞에서부터 거꾸로 채워나간다(PushFront) -> 7 4 2 (1 4)
        dq.PushFront(input);

        //M개만 출력하면 되므로 M개 이상 되면 중단
        ++queueSize;
        if (queueSize > M) {
            break;
        }
    }

    //M개만큼 뒤에서 출력
    for (int i = 0; i < M; ++i) {
        std::cout << dq.Back() << ' ';
        dq.PopBack();
    }

    return 0;
}
