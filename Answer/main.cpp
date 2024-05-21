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

using uint = unsigned int;
void HanoiRecursive(uint _curLevel, uint _from, uint _to, uint _temp) {
    if (_curLevel == 0) { 
        return; 
    }

    //가장 작은 원반부터 옮기기 시작(1차 재귀) - temp와 to에 번갈아가면서 쌓아준다.
    HanoiRecursive(_curLevel - 1, _from, _temp, _to);

    //내 원반을 목표 봉에 넣어주고
    std::cout << _from << ' ' << _to << '\n';

    //temp 봉에 옮겨놓은 나보다 작은 원반들을 목표 봉으로 옮겨준다(2차 재귀)
    HanoiRecursive(_curLevel - 1, _temp, _to, _from);
}

void Hanoi(uint _levels) {
    uint trials = 1;
    for (uint i = 0; i < _levels; ++i) {
        trials *= 2;
    }
    trials -= 1;
    std::cout << trials << '\n';

    HanoiRecursive(_levels, 1u, 3u, 2u);
}

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    uint N{}; std::cin >> N;

    Hanoi(N);
    
    return 0;
}
