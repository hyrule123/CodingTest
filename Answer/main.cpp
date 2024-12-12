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
백준 11404 (플로이드) [길찾기][플로이드-워셜][복습]
*/
using uint = unsigned int;
constexpr uint INF = (uint)1e9;
uint n, m, edges[101][101];

void solve() {
	cin >> n >> m;

	for (uint i = 1; i <= n; ++i) {
		for (uint j = 1; j <= n; ++j) {
			if (i != j) { edges[i][j] = INF; }
		}
	}
	for (uint i = 1; i <= m; ++i) {
		uint a, b, c; cin >> a >> b >> c;
		edges[a][b] = min(edges[a][b], c);
	}

	for (uint stopover = 1; stopover <= n; ++stopover) {
		for (uint from = 1; from <= n; ++from) {
			for (uint to = 1; to <= n; ++to) {
				edges[from][to] = min(edges[from][to], edges[from][stopover] + edges[stopover][to]);
			}
		}
	}

	for (uint i = 1; i <= n; ++i) {
		for (uint j = 1; j <= n; ++j) {
			cout << (edges[i][j] == INF ? 0 : edges[i][j]) << ' ';
		}
		cout << '\n';
	}
}