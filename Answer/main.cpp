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
void Heapify(std::vector<int>& _arr, const size_t _size, const size_t _idx) {
    size_t largestIdx = _idx;
    size_t left = _idx * 2 + 1;
    size_t right = left + 1;

    if (left < _size && _arr[largestIdx] < _arr[left]) {
        largestIdx = left;
    }
    if (right < _size && _arr[largestIdx] < _arr[right]) {
        largestIdx = right;
    }

    if (largestIdx != _idx) {
        std::swap(_arr[largestIdx], _arr[_idx]);

        Heapify(_arr, _size, largestIdx);
    }
}

void HeapSort(std::vector<int>& _arr) {
    for (size_t i = _arr.size() / 2; i != -1; --i) {
        Heapify(_arr, _arr.size(), i);
    }

    for (size_t i = _arr.size() - 1; i != -1; --i) {
        //0번은 정렬됨 -> 맨 뒤로 보내고 그거 제외한 부분만 Heapify
        std::swap(_arr[0], _arr[i]);
        Heapify(_arr, i, 0);
    }
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
    HeapSort(numbers);

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
