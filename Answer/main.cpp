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
#include <cmath>

void DivideAndConquer(std::vector<int>& _arr, std::vector<int>& _temp, size_t _begin, size_t _end) {
    if (_begin >= _end) { return; }

    const size_t mid = _begin + (_end - _begin) / 2;
    DivideAndConquer(_arr, _temp, _begin, mid);
    DivideAndConquer(_arr, _temp, mid + 1, _end);

    size_t l = _begin;
    size_t r = mid + 1;
    size_t cursor = _begin;
    while (l <= mid && r <= _end) {
        if (_arr[l] < _arr[r]) {
            _temp[cursor] = _arr[l];
            ++cursor;
            ++l;
        }
        else {
            _temp[cursor] = _arr[r];
            ++cursor;
            ++r;
        }
    }

    //참고: if guard 해도 계산시간 변동은 없었음.
    for (; l <= mid; ++l) {
        _temp[cursor] = _arr[l];
        ++cursor;
    }
    for (; r <= _end; ++r) {
        _temp[cursor] = _arr[r];
        ++cursor;
    }
    
    memcpy(_arr.data() + _begin, _temp.data() + _begin, (_end + 1 - _begin) * sizeof(int));
}

void MergeSort(std::vector<int>& _arr) {
    if (_arr.size() <= 1) { return; }

    std::vector<int> temp{}; temp.resize(_arr.size());
    DivideAndConquer(_arr, temp, 0, _arr.size() - 1);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{}; std::cin >> N;
    std::vector<int> numbers((size_t)N);

    int sum = 0;
    for (int i = 0; i < N; ++i) {
        std::cin >> numbers[i];
        sum += numbers[i];
    }
    MergeSort(numbers);

    //ArithMean
    int arithMean = (int)(std::round((float)sum / (float)numbers.size()));
    std::cout << arithMean << '\n';

    //Median: N은 무조건 홀수이므로 /2만해줘도 됨
    std::cout << numbers[numbers.size() / 2] << '\n';

    //Mode
    std::vector<int> modes{}; modes.reserve(2);
    int modeCount = 1;
    int curNum = numbers[0];
    int curNumCount = 0;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (curNum == numbers[i]) {
            ++curNumCount;
        }
        //숫자 바뀔경우 평가 후 current 초기화
        else {
            if (modeCount < curNumCount) {
                modes.clear();
                modes.push_back(curNum);
                modeCount = curNumCount;
            }
            else if (modeCount == curNumCount && modes.size() < 2) {
                modes.push_back(curNum);
            }

            curNum = numbers[i];
            curNumCount = 1;
        }
    }
    //마지막 숫자 평가
    if (modeCount < curNumCount) {
        modes.clear();
        modes.push_back(curNum);
        modeCount = curNumCount;
    }
    else if (modeCount == curNumCount && modes.size() < 2) {
        modes.push_back(curNum);
    }
    std::cout << (modes.size() == 1 ? modes[0] : modes[1]) << '\n';

    //Range
    std::cout << numbers.back() - numbers.front();
    
    return 0;
}
