#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//https://school.programmers.co.kr/questions/52569

vector<vector<int>> dp; //i번째 던전까지 누적 사용한 피로도 j

int solution(int k, vector<vector<int>> dungeons) {
    constexpr int req = 0, use = 1;
    sort(dungeons.begin(), dungeons.end(),
        [](const vector<int>& a, const vector<int>& b)->bool {
            return (a[req] - a[use]) < (b[req] - b[use]);
        }
        );

    dp.resize(dungeons.size() + 1, vector<int>((size_t)(k + 1)));

    for (size_t i = 1; i < dp.size(); ++i) {
        for (size_t j = 1; j < dp[i].size(); ++j) {
            size_t dungeon_idx = i - 1;
            //i 던전에 필요한 피로도보다 j가 작으면 입장 x
            if (j < dungeons[dungeon_idx][req]) {
                dp[i][j] = dp[i - 1][j];
            }
            //i 던전에 입장 가능할 경우
            // : 입장 안할때와 입장 했을 때중 더 많은 입장횟수 쪽을 선택
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - dungeons[dungeon_idx][use]] + 1);
            }
        }
    }

    return dp.back().back();
}

int main() {
    auto ans = solution(80, { {80, 20}, {50, 40}, {30, 10} });

    return 0;
}