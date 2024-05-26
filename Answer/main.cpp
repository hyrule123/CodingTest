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
#include <array>
using uint = unsigned int;

size_t minGap = std::numeric_limits<size_t>::max();

std::vector<std::vector<size_t>> synergyScores{};

std::vector<bool> occupied{};
std::vector<size_t> teamANumber{};
std::vector<size_t> teamBNumber{};
size_t N{};
size_t teamSize{};

void Recursive() {
    //팀 A가 결정됐을 경우, 팀 B는 자동 결정됨.
    if (teamSize == teamANumber.size()) {
        size_t scoreA{}, scoreB{};
 
        //시너지 점수 합 계산 후 return
        teamBNumber.clear();
        for (size_t i = 0; i < N; ++i) {
            if (false == occupied[i]) {
                teamBNumber.push_back(i);
            }
        }
        
        for (size_t i = 0, iEnd = teamSize - 1; i < iEnd; ++i) {
            for (size_t j = i + 1; j < teamSize; ++j) {
                size_t idx = teamANumber[i];
                size_t jdx = teamANumber[j];

                scoreA += synergyScores[idx][jdx] + synergyScores[jdx][idx];
                
                idx = teamBNumber[i];
                jdx = teamBNumber[j];
                scoreB += synergyScores[idx][jdx] + synergyScores[jdx][idx];
            }
        }

        size_t gap = scoreA > scoreB ? scoreA - scoreB : scoreB - scoreA;
        if (gap < minGap) { minGap = gap; }

        return;
    }

    //A팀에 넣을 선수 번호, 오름차순으로만(이러면 중복되지 않음)
    for (size_t n = teamANumber.back() + 1; n < N; ++n) {
        teamANumber.push_back(n);
        occupied[n] = true;

        Recursive();
        if (minGap == 0) { return; }

        occupied[n] = false;
        teamANumber.pop_back();
    }
}

void DivideTeam() {
    teamSize = synergyScores.size() / 2;
    teamANumber.reserve(teamSize);
    teamBNumber.reserve(teamSize);

    //A팀을 구성하면 B팀은 자동 확정되므로, A팀만 뽑아준다.
    //2n명의 구성원을 n명/n명 중복 및 순서 없이 나눠야 한다.
    //오름차순으로 구성할 시 중복 및 순서가 모두 제외된다.
    //무조건 A팀에 B팀보다 낮은 수가 들어가야 하므로(오름차순), 0(1번선수)을 넣어준다.
    //ex)134 / 256 -> 256 / 134 등의 중복 경우가 제외됨.    
    teamANumber.push_back(0u);
    occupied.resize(N);
    occupied[0] = true;

    Recursive();
    std::cout << minGap;
}

int main() { 
    READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

    std::cin >> N;
    synergyScores.resize(N, std::vector<size_t>(N));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cin >> synergyScores[i][j];
        }
    }
    DivideTeam();

    return 0;
}
