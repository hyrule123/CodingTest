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
백준 14852 (타일 채우기 3) [DP][v2][9832kb][12ms]
v1: 첫번째 풀이 [17644kb][12ms]
v2: 누적합만 사용하여 메모리 사용 줄인 버전 [9832kb][12ms]

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
constexpr ll mod = 1'000'000'007;

ll dp[1'000'001];

void solve()
{
	ll N; cin >> N;
	dp[1] = 2;
	dp[2] = 2 + 7;
	for (ll i = 3; i <= N; ++i)
	{
		//i - 2가 mod로 나눠져서 더 작은수일수도 있으므로 mod를 더해준다.
		ll prev2 = (mod + dp[i - 2] - dp[i - 3]) % mod;

		/*
		dp[i] = dp[i - 1] * 2 + dp[i - 2] * '3' + dp[i - 4] * 2 * ... * dp[1] * 2 + 2
			== partsum[i - 1] * 2 + (partsum[i - 2] - partsum[i - 3]) + 2
		-> 2로 묶고, dp[i-2]만 따로 한번 더해줌
		*/
		ll cur = (dp[i - 1] * 2 + prev2 + 2) % mod;
		dp[i] = (dp[i - 1] + cur) % mod;
	}

	cout << (mod + dp[N] - dp[N - 1]) % mod;
}