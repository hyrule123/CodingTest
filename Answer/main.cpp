#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}
/*
백준 1006 (습격자 초라기)
W: 소대가 처리할 수 있는 적의 수
E[MAX][2]: 해당 거점 적의 수
DP[MAX][3]
DP[i][0] INNER : 배열을 i-1까지 채우고, i번째 INNER에 소대를 투입하는 경우(┌)
DP[i][1] OUTER: 배열을 i-1까지 채우고, i번째 OUTER에 소대를 투입하는 경우(└)
DP[i][2] ALL: 배열을 N까지 점령하는데 필요한 최소 소대 수

DP[i][0]
초기화: DP[i-1][2] + 1
E[i-1][0] + E[i][0] <= W인 경우(한소대로 두 구획을 점령 가능한 경우)
DP[i][0] = min(DP[i][0], DP[i-1][1] + 1)
->└ + 1

DP[i][1]
초기화: DP[i-1][2] + 1
E[i-1][1] + E[i][1] <= W인 경우(한소대로 두 구획을 점령 가능한 경우)
DP[i-1][1] = min(DP[i][1], DP[i-1][0] + 1)
-> ┌ + 1

DP[i][2]
초기화: min(DP[i][0] + 1, DP[i][1] + 1)
나머지 안채운 한 구획에 소대를 투입시키므로 + 1

E[i][0] + E[i][1] <= W 병합이 가능할 경우:
DP[i][2] = min(DP[i][2], DP[i-1][2] + 1)

+ INNER, OUTER 둘 다 병합이 가능한경우도 고려해줘야 한다.
2 <= i && E[i-1][0] + E[i][0] <= W && E[i-1][1] + E[i][1] <= W
DP[i][2] = min(DP[i][2], DP[i-2][2] + 2)

//원형 배열 -> 처음과 끝 연결 작업
1. INNER, OUTER 모두 연결 안할 경우
DP[0][0] = DP[0][1] = DP[0][2] = 0 하고 DPFUNC(1) 호출
DP[N][2]에 답이 들어있다

2. INNER만 연결 가능할 경우: 일단 제외시키고 DP계산 한 후 해당 경우의 수를 더한다.
... N 1 2 ...
	1 3
	2 4
-> 1, 3 연결된 상태를 가정
DP[1][0]: 0 설정 후 DP 계산
결과: DP[N][0] + 1 (E[N][1]에 1소대)


3. OUTER만 연결 가능할 경우
-> 2, 4
DP[1][1]: 0 설정 후 DP 계산
결과: DP[N][1] + 1 (E[N][0]에 1소대)

4. INNER + OUTER 모두 연결 가능한 경우
DP[1][0] = DP[1][1] = DP[1][2] 모두 0
결과: DP[N-1][2] + 2
*/

using uint = unsigned int;

constexpr uint MAX = 10001, INF = 987654321;
constexpr int INNER = 0, OUTER = 1, ALL = 2;
uint N, W, enemies[MAX][2], dp[MAX][3];

inline void dpsub_inner(uint last, uint cur) {
	dp[cur][INNER] = dp[last][ALL] + 1;
	if (enemies[last][INNER] + enemies[cur][INNER] <= W) {
		dp[cur][INNER] = min(dp[cur][INNER], dp[last][OUTER] + 1);
	}
}
inline void dpsub_outer(uint last, uint cur) {
	dp[cur][OUTER] = dp[last][ALL] + 1;
	if (enemies[last][OUTER] + enemies[cur][OUTER] <= W) {
		dp[cur][OUTER] = min(dp[cur][OUTER], dp[last][INNER] + 1);
	}
}
inline void dpsub_all(uint last, uint cur) {
	dp[cur][ALL] = min(dp[cur][INNER] + 1, dp[cur][OUTER] + 1);

	if (enemies[cur][INNER] + enemies[cur][OUTER] <= W) {
		dp[cur][ALL] = min(dp[cur][ALL], dp[last][ALL] + 1);
	}

	if (0 <= last - 1 &&
		enemies[last][INNER] + enemies[cur][INNER] <= W &&
		enemies[last][OUTER] + enemies[cur][OUTER] <= W
		) {
		dp[cur][ALL] = min(dp[cur][ALL], dp[last - 1][ALL] + 2);
	}
}

void DP(uint start) {
	for (uint i = start; i <= N; ++i) {
		dpsub_inner(i - 1, i);
		dpsub_outer(i - 1, i);
		dpsub_all(i - 1, i);
	}
}

void solve() {
	uint TC; cin >> TC;
	while (TC--) {
		cin >> N >> W;

		for (uint j = 0; j <= 1; ++j) {
			for (uint i = 1; i <= N; ++i) {
				cin >> enemies[i][j];
			}
		}

		//N이 1일 경우에는 앞뒤 연결이 없음
		//붙이거나 각자 파견하거나
		if (N == 1) {
			uint ans = (enemies[1][INNER] + enemies[1][OUTER] <= W ? 1 : 2);
			cout << ans << '\n';
			continue;
		}

		dp[0][INNER] = dp[0][OUTER] = dp[0][ALL] = 0;
		enemies[0][INNER] = enemies[0][OUTER] = INF;

		uint ans = 0xff'ff'ff'ff;

		//앞뒤 연결 안한 경우
		DP(1);

		ans = min(ans, dp[N][ALL]);

		//앞뒤의 INNER 연결만 확정일 경우(1개 소대로 2개구역 커버)
		//이미 커버된 해당 구역을 제외하고 DP 돌린후 + 1
		//N INNER, 1 INNER 제외 -> N OUTER까지만 DP 구한뒤 + 1
		if (enemies[N][INNER] + enemies[1][INNER] <= W) {
			//INNER은 연결 된 상태: 경우의수에서 제외
			dp[1][INNER] = 0;

			//OUTER은 연결 안되었다고 가정
			dp[1][OUTER] = 1;

			//INNER, OUTER 통틀어 확인
			dpsub_all(0, 1);

			//2부터 시작
			DP(2);

			//N INNER과 1 INNER은 연결 되었으므로
			//N OUTER까지만 구한 뒤 연결된 소대 1을 더해준다
			ans = min(ans, dp[N][OUTER] + 1);

			enemies[0][OUTER] = INF;
		}

		//앞뒤의 OUTER 연결만 확정일 경우(1개 소대로 2개구역 커버)
		//이미 커버된 해당 구역을 제외하고 DP 돌린후 + 1
		//N OUTER, 1 OUTER 제외 -> N INNER까지만 DP 구한뒤 + 1
		if (enemies[N][OUTER] + enemies[1][OUTER] <= W) {
			dp[0][INNER] = 1;
			dp[1][OUTER] = 0;

			//INNER 검사
			enemies[0][INNER] = enemies[N][INNER];
			dpsub_inner(0, 1);
			dpsub_all(0, 1);

			DP(2);
			ans = min(ans, dp[N][INNER] + 1);

			enemies[0][INNER] = INF;
		}

		//위, 아래 둘다 연결 가능할 경우(2소대로 4개구역 커버)
		//4개 구역을 제외하고 DP돌린후 마지막에 2개 더한다
		if (enemies[N][INNER] + enemies[1][INNER] <= W &&
			enemies[N][OUTER] + enemies[1][OUTER] <= W) {

			dp[1][INNER] = dp[1][OUTER] = dp[1][ALL] = 0;
			DP(2);
			ans = min(ans, dp[N - 1][ALL] + 2);
		}

		cout << ans << '\n';
	}
}
