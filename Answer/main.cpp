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

struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;
    int data = 0;
};

//doubly linked list로 구현해봄
struct deque {
    deque() : size(0) { begin.next = &end; end.prev = &begin; begin.data = -1; end.data = -1; }
    ~deque() {
        Node* todelete = begin.next;
        while (todelete != &end) {
            Node* temp = todelete;
            todelete = todelete->next;
            delete temp;
        }
    }

    inline bool Empty() { return (size == 0); }
    inline int Size() { return size; }

    inline void PushFront(int _u) {
        Node* temp = begin.next;

        begin.next = new Node;
        begin.next->data = _u;
        begin.next->next = temp;
        begin.next->prev = &begin;

        temp->prev = begin.next;
        ++size;
    }
    inline void PushBack(int _u) {
        Node* temp = end.prev;

        end.prev = new Node;
        end.prev->data = _u;
        end.prev->prev = temp;
        end.prev->next = &end;

        temp->next = end.prev;
        ++size;
    }
    inline void PopFront() {
        if (false == Empty()) {
            Node* temp = begin.next;

            begin.next = temp->next;
            begin.next->prev = &begin;
            delete temp;
            --size;
        }
    }
    inline void PopBack() {
        if (false == Empty()) {
            Node* temp = end.prev;

            end.prev = temp->prev;
            end.prev->next = &end;
            delete temp;
            --size;
        }
    }
    inline int Front() { return begin.next->data; }
    inline int Back() { return end.prev->data; }

    Node begin;
    Node end;
    int size;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    /* TC Generation Code */
    //{
    //    srand(time(0));
    //    int gen = 1000000;
    //    int inserts = 0;
    //    std::cout << gen << '\n';
    //    for (int i = 0; i < gen; ++i) {
    //        int com = 1 + rand() % 8;
    //        std::cout << com;
    //        if (com == 1 || com == 2) {
    //            std::cout << ' ' << (1 + rand() % 10000);
    //            ++inserts;
    //        }
    //        std::cout << '\n';
    //    }
    //    std::cout << "Inserts: " << inserts;

    //    return 0;
    //}

    deque dq{};

    int N{}; std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int command{}; std::cin >> command;
        
        if (command == 1) {
            int input{}; std::cin >> input;
            dq.PushFront(input);
        }
        else if (command == 2) {
            int input{}; std::cin >> input;
            dq.PushBack(input);
        }
        else if (command == 3) {
            std::cout << dq.Front() << '\n';
            dq.PopFront();
        }
        else if (command == 4) {
            std::cout << dq.Back() << '\n';
            dq.PopBack();
        }
        else if (command == 5) {
            std::cout << dq.Size() << '\n';
        }
        else if (command == 6) {
            std::cout << (int)dq.Empty() << '\n';
        }
        else if (command == 7) {
            std::cout << dq.Front() << '\n';
        }
        else if (command == 8) {
            std::cout << dq.Back() << '\n';
        }
    }

    return 0;
}
