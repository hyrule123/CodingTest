#include <string>
#include <vector>
#include <array>
using namespace std;

//연결된 사이클이므로 끊어줘야함
//첫번째 집 감 -> 마지막 집 못감
//첫번째 집 안감 -> 마지막 집 감
struct choose {
    array<int, 2> first_go, first_no;
};
vector<choose> dp;
constexpr int NO = 0, GO = 1;

//이번 집을 터느냐 안터느냐
int solution(vector<int> money) {
    int answer = 0;

    dp.resize(money.size());

    //마지막 집 수동 설정
    //첫 집을 안가는 경우에만 마지막 집을 방문한다는 선택지 가능
    dp.back().first_no[GO] = money.back();

    //마지막 전 집부터 차례대로 순회
    for (int i = (int)money.size() - 2; 0 <= i; --i) {
        dp[i].first_go[GO] = money[i];
        dp[i].first_no[GO] = money[i];

        //이번 집을 털면 다음 집은 못 턴다
        dp[i].first_go[GO] += dp[i + 1].first_go[NO];
        //안 털면 다음 집은 털어도되고 안털어도 된다
        dp[i].first_go[NO] += max(dp[i + 1].first_go[GO], dp[i + 1].first_go[NO]);
        dp[i].first_no[GO] += dp[i + 1].first_no[NO];
        dp[i].first_no[NO] += max(dp[i + 1].first_no[GO], dp[i + 1].first_no[NO]);
    }

    answer = max(dp[0].first_go[GO], dp[0].first_no[NO]);

    return answer;
}

int main() {
    auto ans = solution({ 1, 2, 3, 1 });
    return 0;
}