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

#include <array>
#include <vector>
//백준 11438 (LCA 2)
//parent_of == 합성함수 f, parent_of[i][j]: j 노드의 i번째 부모 노드 번호
//노드가 N개일때 가능한 부모 모드의 최대값 = N - 1: 100000 -> log2(100000) = 16.6...
constexpr int LOG_MAX = 18, MAX = 100001;
int N, M, parent_of[LOG_MAX][MAX], depths[MAX];
array<vector<int>, MAX> graph;

//합성함수(dp) 빌드
void build_parent_of(int par, int cur, int depth) {
	parent_of[0][cur] = par;
	depths[cur] = depth;

	for (int child : graph[cur]) {
		if (child == par) { continue; }
		build_parent_of(cur, child, depth + 1);
	}
}

void precompute() {
	for (int shift = 1; shift < LOG_MAX; ++shift) {
		for (int i = 1; i <= N; ++i) {
			//dp: f(n, k) = f(n-1, f(n-1, k))...
			parent_of[shift][i] = parent_of[shift - 1][parent_of[shift - 1][i]];
		}
	}
}

int LCA(int l, int r) {
	//depth가 더 깊은 쪽을 오른쪽으로
	if (depths[l] > depths[r]) {
		swap(l, r);
	}

	//깊이 차이를 구한다
	int depth_diff = depths[r] - depths[l];

	//깊은 쪽(r)을 깊이차이만큼 올려서 균형을 맞춰준다.
	/* ex
	 1
	 2
	3 4 
	5 6 <- 여기로 이동해서 깊이를 일치시킴 l = 5, r = 6
	7 8 
	  9 <- 여기서 시작(l = 5, r = 9)
	*/
	for (int i = 0; i < LOG_MAX; ++i) {
		int bit = 1 << i;
		if (depth_diff < bit) { break; }
		if (depth_diff & bit) {
			r = parent_of[i][r];
		}
	}

	//동일 부모를 발견했을 경우 해당 부모를 리턴한다.
	if (l == r) {
		return l;
	}

	//높이를 맞췄으므로 높이만큼 탐색을 진행
	//'서로 다른 부모 노드' 중 '가장 먼' 부모 노드를 탐색한다.(멀리서부터 탐색해야 함)
	//그럼 찾은 노드의 부모 노드는 '가장 가까운' 공통 노드(최소 공통 조상)이 된다.
	/* ex
	 1
	 2 
	3 4 <- 여길 찾는것
	5 6 <- 여기서 시작
	7 8 
	  9
	*/
	for (int i = LOG_MAX - 1; i >= 0; --i) {
		if (parent_of[i][l] == parent_of[i][r]) { continue; }
		l = parent_of[i][l];
		r = parent_of[i][r];
	}
	
	//l의 부모 노드를 리턴
	return parent_of[0][l];
}

void solve() {
	cin >> N;
	for (int i = 1; i <= N - 1; ++i) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	//1을 루트로 하는 그래프에서 합성함수를 생성
	build_parent_of(0, 1, 0);

	//사전 계산
	precompute();

	//LCA 수행
	cin >> M;
	while (M--) {
		int l, r; cin >> l >> r;
		cout << LCA(l, r) << '\n';
	}
}