#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL
#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
//////////////////

struct myVec {
    myVec() : arr{}, size{ 0 }, capacity{ 0 } {}
    ~myVec() { delete[] arr; }

    void Reserve(int _capacity) {
        capacity = _capacity; 
        arr = new int[capacity]; 
        memset(arr, 0, sizeof(int) * capacity);
    }
    bool Empty() { return 0 == size; }
    void PushBack(int _i) { arr[size] = _i; ++size; }
    void PopBack() { --size; }

    int operator[](int _idx) { return arr[_idx]; }

    int* arr;
    int size;
    int capacity;
};

int ABS(int _i) { return _i < 0 ? -_i : _i; }

int Recursive(myVec& _boardRows, const int _max) {
    if (_boardRows.size == _max) {
        for (int i = 0; i < _boardRows.size; ++i) {
        }
        return 1;
    }

    int cases = 0;
    //i: 이번 row에 놓을 퀸
    for (int i = 0; i < _max; ++i) {
        int curRow = _boardRows.size;

        bool cont = false;
        //j: 이전 row들에 놓여있는 퀸의 col 번호
        for (int j = 0; j < _boardRows.size; ++j) {
            //i열에 이미 퀸이 놓여 있거나, 대각선에 퀸이 있을 경우 중단
            //대각선은 거리마다 1 증가, 대각선인지만 알면 되므로 절댓값으로 한번에 판단가능
            int dist = curRow - j;
            if (i == _boardRows[j] || ABS(i - _boardRows[j]) == dist) {
                cont = true;
                break;
            }
        }

        if (cont) { continue; }

        _boardRows.PushBack(i);
        cases += Recursive(_boardRows, _max);
        _boardRows.PopBack();
    }

    return cases;
}

int nQueen(int _n) {
    myVec arr{}; arr.Reserve(_n);
    return Recursive(arr, _n);
}

int main() { 
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    int N{}; std::cin >> N;
    std::cout << nQueen(N);

    return 0;
}
