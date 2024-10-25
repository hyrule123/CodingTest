#include <string>
#include <vector>
using namespace std;

constexpr int p = 1'000'000'007;
constexpr int BLOCK = -1;
vector<vector<int>> memo;

//m = col, n = row
int solution(int m, int n, vector<vector<int>> puddles) {
    memo.resize(n + 1, vector<int>((size_t)(m + 1)));
    for (const vector<int>& pud : puddles) {
        memo[pud[1]][pud[0]] = BLOCK;
    }

    //[1][1]을 1로 만들어주기 위해서 설정
    memo[0][1] = 1;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            //BLOCK은 이동 불가, BLOCK으로부터 오는것도 불가
            if (memo[r][c] != BLOCK) {
                if (memo[r - 1][c] != BLOCK) {
                    memo[r][c] += memo[r - 1][c];
                }
                if (memo[r][c - 1] != BLOCK) {
                    memo[r][c] += memo[r][c - 1];
                }
                memo[r][c] %= p;
            }
        }
    }

    return memo[n][m];
}

int main() {
    auto ans = solution(4, 3, { {2, 2} });
    return 0;
}