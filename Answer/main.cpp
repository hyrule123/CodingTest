#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;
void solve();
int main()
{
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

/*
백준 14852 (타일 채우기 3) [DP][v1][17644kb][12ms]
v1: 첫 번째 풀이

* 위 또는 아래에 ㅡㅡ(1 * 2)를 채울 경우: 4칸을 고려해야함
	ㅡㅡ		ㅡㅡ		ㅁㅁ
	ㅁㅁ		ㅡㅡ		ㅡㅡ
	3가지 경우가 있을 수 있다 -> DP[x - 2] * 3

* ㅣ 또는 ㅁ을 채울 경우: 2칸을 고려하면 됨
	ㅣ	ㅁ
	ㅣ	ㅁ

* 또한, 길이가 3 이상인 벽(2 * x)부터 2개씩 유니크 패턴이 추가됨
	3을 예로 들면
	ㅡㅡ ㅁ		ㅁ ㅡㅡ
	ㅁ ㅡㅡ		ㅡㅡ ㅁ
	4를 예로 들면
	ㅡㅡ  ㅡㅡ		ㅁ ㅡㅡ ㅁ
	ㅁ ㅡㅡ ㅁ		ㅡㅡ  ㅡㅡ

	그러니까, 길이 6까지 타일을 채우는 방법은
	DP[6] = DP[5] * 2 + DP[4] * 3
		+ DP[3] * 2 (길이 3을 채우는 방법의 수 + 길이 3짜리 유니크 패턴 2개)
		+ DP[2] * 2 (길이 2를 채우는 방법의 수 + 길이 4짜리 유니크 패턴 2개)
		+ DP[1] * 2 (길이 1을 채우는 방법의 수 + 길이 5짜리 유니크 패턴 2개)
	매번 1 ~ x - 3까지 순회돌면서 *2를 해주는 건 매우 비효율적이므로
	길이 3 이상부터 유니크 패턴이 생기므로, 누적합으로 별도로 저장해야 한다.
*/
using ll = long long;
constexpr ll mod = 1'000'000'007, cur = 0, partsum = 1;

ll dp[1'000'001][2];

void solve()
{
	ll N; cin >> N;
	dp[1][cur] = 2;
	dp[1][partsum] = 2;
	dp[2][cur] = 7;
	dp[2][partsum] = 2 + 7;
	for (ll i = 3; i <= N; ++i)
	{
		dp[i][cur] =
			dp[i - 1][cur] * 2 //세로
			+ dp[i - 2][cur] * 3 //가로 2 * 2칸을 채우는 방법
			+ 2	//이번 길이에서 생성된 유니크 패턴 2개
			+ dp[i - 3][partsum] * 2; //1~(i - 3)까지 채우는 방법에 유니크 패턴을 채우는 방법의 수
		dp[i][cur] %= mod;

		//구간합 계산
		dp[i][partsum] = dp[i - 1][partsum] + dp[i][cur];
		dp[i][partsum] %= mod;
	}

	cout << dp[N][cur];
}