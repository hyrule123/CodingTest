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
백준 1005 (ACM Craft)
//재귀호출 최대한 줄인 버전
*/
#include <vector>
constexpr int MAX = 1001;
int N, K, buildtimes[MAX], memo[MAX];	//memo[i]: i를 짓기 위해 필요한 시간
vector<int> req_build[MAX];	//선행 빌드
void clear(int size) {
	memset(memo + 1, -1, sizeof(int) * size);
	for (int i = 1; i <= size; ++i) {
		req_build[i].clear();
	}
}

void get_min_buildtime(int cur) {
	memo[cur] = 0;
	//가장 늦게 완료되는 노드까지 기다려줘야 함
	for (int next : req_build[cur]) {
		if (-1 == memo[next]) {
			get_min_buildtime(next);
		}
		memo[cur] = max(memo[cur], memo[next]);
	}
	memo[cur] += buildtimes[cur];
}

void solve() {
	int T; cin >> T;
	while (T--) {
		cin >> N >> K;
		clear(N);

		for (int i = 1; i <= N; ++i) {
			cin >> buildtimes[i];
		}
		for (int i = 1; i <= K; ++i) {
			int x, y; cin >> x >> y;
			req_build[y].push_back(x);
		}

		//건물 번호
		int w; cin >> w;
		get_min_buildtime(w);
		cout << memo[w] << '\n';
	}
}
