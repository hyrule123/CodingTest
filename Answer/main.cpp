#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
namespace op { enum E { add, sub, mul, div, end }; };

struct MinMax { int Min{ std::numeric_limits<int>::max() }, Max{ std::numeric_limits<int>::min() }; };

void Recursive(std::vector<int>& _numOrder, std::vector<int>& _operators, MinMax& _minMax, const size_t _curIdx, const int _prevResult) {
    if (_numOrder.size() == _curIdx) {
        if (_minMax.Max < _prevResult) { _minMax.Max = _prevResult; }
        if (_minMax.Min > _prevResult) { _minMax.Min = _prevResult; }
        return;
    }

    for (size_t i = 0; i < _operators.size(); ++i) {
        if (0 < _operators[i]) {
            int result = _prevResult;
            if (i == op::add) { result += _numOrder[_curIdx]; }
            else if (i == op::sub) { result -= _numOrder[_curIdx]; }
            else if (i == op::mul) { result *= _numOrder[_curIdx]; }
            else if (i == op::div) { result /= _numOrder[_curIdx]; }

            --(_operators[i]);
            Recursive(_numOrder, _operators, _minMax, _curIdx + 1, result);
            ++(_operators[i]);
        }
    }

}

void InsertOperator(std::vector<int>& _numOrder, std::vector<int>& _operators) {
    MinMax minMax{};
    Recursive(_numOrder, _operators, minMax, 1, _numOrder[0]);
    std::cout << minMax.Max << '\n' << minMax.Min;
}

int main() { 
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    int N{}; std::cin >> N;
    std::vector<int> numOrder((size_t)N);
    std::vector<int> operators((size_t)op::end);
    for (int i = 0; i < N; ++i) {
        std::cin >> numOrder[i];
    }
    for (int i = 0; i < op::end; ++i) {
        std::cin >> operators[i];
    }

    InsertOperator(numOrder, operators);

    return 0;
}
