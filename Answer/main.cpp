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
struct stack {
    stack(size_t _size) { cont.resize(_size); stackPos = -1; }
    bool Empty() { return (stackPos < 0); }
    void Insert(int _num) { ++stackPos; cont[stackPos] = _num; }
    int* Last() { if (false == Empty()) { return &(cont[stackPos]); } return nullptr; }
    void Pop() { if (false == Empty()) { --stackPos; } }

    std::vector<int> cont;
    int stackPos;
};

struct queue {
    queue(size_t _size) { cont.reserve(_size); queuePos = 0; }

    bool Empty() { return (queuePos == cont.size()); }
    void Insert(int _num) { cont.push_back(_num); }
    int* First() { if (false == Empty()) { return &(cont[queuePos]); } return nullptr; }
    void Pop() { if (false == Empty()) { ++queuePos; } }

    std::vector<int> cont;
    size_t queuePos;
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    queue origLine(1000);
    stack tempLine(1000);

    bool found1 = false;
    int N{}; std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int input; std::cin >> input;

        if (1 == input) {
            found1 = true;
        }

        if (false == found1) {
            tempLine.Insert(input);
        }
        else {
            origLine.Insert(input);
        }
    }

    int prevNumber = 0;
    int nextNumber = 1;
    while (true) {
        //원래 줄에서 nextNumber 나오는동안 계속 입장
        while (false == origLine.Empty() && nextNumber == *(origLine.First())) {
            origLine.Pop();
            ++nextNumber;
        }

        //임시 줄에서 nextNumber 나오는동안 계속 입장
        while (false == tempLine.Empty() && nextNumber == *(tempLine.Last())) {
            tempLine.Pop();
            ++nextNumber;
        }

        //둘 중 하나도 입장 못했을 경우(nextNumber 진전 없을경우)
        if (prevNumber == nextNumber) {
            while (true) {
                //원래 줄에서 nextNumber 찾을때까지 임시줄로 옮겨준다
                if (false == origLine.Empty()) {
                    if (nextNumber == *(origLine.First())) {
                        break;
                    }

                    tempLine.Insert(*(origLine.First()));
                    origLine.Pop();
                }
                //다 옮길때까지 못찾았으면 도저히 방법이 없는것
                else {
                    std::cout << "Sad";
                    return 0;
                }
            }

        }

        //마지막 번호까지 다 들어갔을 경우 성공한 것
        if (N < nextNumber) {
            std::cout << "Nice";
            return 0;
        }

        prevNumber = nextNumber;
    }

    return 0;
}
