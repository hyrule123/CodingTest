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

#include <array>
#include <vector>
using sBoard = std::array<std::array<int, 9>, 9>;
sBoard board{};

struct answer {
    int r{}, c{}, groupR{}, groupC{};
    std::vector<int> possibleCases{};
    int curCase{};
};

bool Recursive(std::vector<answer>& _answers, const size_t _cur) {
    if (_answers.size() == _cur) { return true; }

    answer& curAns = _answers[_cur];
    for (size_t i = 0; i < curAns.possibleCases.size(); ++i) {

        bool cont = false;

        //지난 재귀에서 선택한 답이 자신과 연관되어 있을 경우 중복된 값이 사용되었는지 검사한다.
        for (size_t j = 0; j < _cur; ++j) {
            if (_answers[j].r == curAns.r
                || _answers[j].c == curAns.c
                || (_answers[j].groupR == curAns.groupR && _answers[j].groupC == curAns.groupC)
                ) 
            {
                //이번에 집어넣고자 하는 값이 이미 사용된 값일 경우 이번 루프 중단
                if (_answers[j].curCase == curAns.possibleCases[i]) {
                    cont = true;
                    break;
                }
            }
        }

        if (cont) { continue; }

        //답 집어넣고 재귀 호출. 답 한개만 구하면 되니까 true 리턴받을 시 바로 true 리턴
        curAns.curCase = curAns.possibleCases[i];
        if (Recursive(_answers, _cur + 1)) { return true; }
    }

    //루프 다돌때까지 찾은게 없으면 false 리턴
    return false;
}

void Sudoku(sBoard& _board, std::vector<answer>& _answers) {
    std::vector<bool> usage;
    for (size_t i = 0; i < _answers.size(); ++i) {
        usage.clear();
        usage.resize(10, false);

        //세로, 가로, 자신이 속한 3x3 그룹을 탐색해서 가능한 정답을 미리 구한다.
        answer& ans = _answers[i];
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                int lineIdx = 3 * r + c;
                usage[_board[ans.r][lineIdx]] = true;
                usage[_board[lineIdx][ans.c]] = true;
                usage[_board[ans.groupR + r][ans.groupC + c]] = true;
            }
        }

        //1부터 9 중에 쓰이지 않은 수를 집어넣는다.
        for (int j = 1; j < 10; ++j) {
            if (false == usage[j]) {
                _answers[i].possibleCases.push_back(j);
            }
        }
    }

    Recursive(_answers, (size_t)0);

    size_t curAnsIdx = 0;
    for (size_t r = 0; r < 9; ++r) {
        for (size_t c = 0; c < 9; ++c) {
            int print = _board[r][c];
            if (print == 0) {
                print = _answers[curAnsIdx].curCase;
                ++curAnsIdx;
            }
            std::cout << print << ' ';
        }
        std::cout << '\n';
    }
}

int main() { 
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    std::vector<answer> answers{};
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            std::cin >> board[r][c];
            if (board[r][c] == 0) {
                answers.push_back(answer{ r, c, r / 3 * 3, c / 3 * 3, {}, 0 });
                answers.back().possibleCases.reserve(9);
            }
        }
    }
    Sudoku(board, answers);

    return 0;
}
