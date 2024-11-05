#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

using namespace std;
int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

//백준 2098 (외판원 순회)
//백준 1311 (할 일 정하기 1) 과 다른 점:
// 1311: 일꾼을 붙이는 데 순서는 중요하지 않다. 각 일꾼 별로 최소값을 찾으면 된다.
// 2098: 방문 순서에 따라 같은 도시를 방문했더라도 결과가 달라질 수 있다.ex)a-b-c-d, a-b-d-c

using uint = unsigned int;
//dp[i][j]: i->방문한 노드들 마스킹 처리, j->마지막으로 도착한 도시 번호(ex. 1234->[0b1111][4], 1243->[0b1111][3])
uint N, costs[16][16], dp[1 << 16][16];
constexpr uint INF = (uint)1e9;

#include <string>
uint TSP(uint visited_mask, uint cur) {
	visited_mask |= 1 << cur;

	//전부 순회를 다 돌았다면 시작 지점(여기서는 0 고정)되돌아올 수 있는지 확인한다.
	if (visited_mask == (1 << N) - 1) {
		//되돌알올 수 없다면 INF를 반환(
		if (costs[cur][0] == 0) {
			return INF;
		}
		return costs[cur][0];
	}

	uint& ret = dp[visited_mask][cur];

	if (ret == -1) {
		ret = INF;
		for (uint i = 0; i < N; ++i) {
			if (cur == i) { continue; }
			if (visited_mask & 1 << i) { continue; }
			if (0 == costs[cur][i]) { continue; }	//0 == 이동 불가

			ret =
				min(ret, TSP(visited_mask, i) + costs[cur][i]);
		}
	}

	return ret;
}

void solve() {
	cin >> N;
	for (uint i = 0; i < N; ++i) {
		for (uint j = 0; j < N; ++j) {
			cin >> costs[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));
	cout << TSP(0, 0);
}