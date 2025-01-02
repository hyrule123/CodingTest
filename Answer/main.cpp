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
백준 24459 (회로의 저항) [DFS]
리프노드부터 리프노드까지의 거리 중 최장거리와 최단거리 구하기
* 유사 문제: 백준 3176 (도로 네트워크)
* LCA를 사용하여 푸는 문제인가...했으나 아닌 듯
마지막에 리프노드의 모든 쌍끼리 거리를 구하는 과정에서 O(N^2)가 될 수도 있음

https://m.kin.naver.com/qna/dirs/10402/docs/471094489
DFS로 찾고 있는듯. 이 코드는 위 사이트를 참고하여 이해하고 주석을 단 뒤 제출하였음.
*/
#include <vector>
using pii = pair<int, int>;
#define dest first
#define dist second
constexpr int imax = (int)1e9, imin = 0;

struct ret_val {
	int min_first = imax, 
		min_second = imax, 
		max_first = imin, 
		max_second = imin;
};

int N, ans_max = imin, ans_min = imax;
vector<pii> edges[100'000];

ret_val DFS(int cur, int prev) {
	ret_val ret{};
	bool path_found = false;
	
	/*
	다음 간선으로 출발
	자신이 임의의 중간 지점의 노드이고
	구해야하는 것은 리프 노드 사이의 최단거리, 최장거리일 경우
	리프 노드까지 DFS 탐색을 한 후 두 최단거리의 합 / 최장거리의 합을 구하면 된다.
	ex.
	다음 노드가 A, B, C 라면
	최단거리는 A, B, C 노드로 이동했을때 3가지 경우를 DFS 돌린 후 가장 가까운 경로 2개와 가장 먼 경로 2개를 선정한 후 합하여 반환한다.
	*/
	for (const pii& next : edges[cur]) {
		if (next.dest == prev) { continue; }
		
		path_found = true;
		ret_val result = DFS(next.dest, cur);

		//이번 DFS 결과에 이번 간선의 길이를 더한다
		int found_dist_min = result.min_first + next.dist;
		int found_dist_max = result.max_first + next.dist;

		//가장 짧은 거리 2개를 저장한다.
		if (found_dist_min < ret.min_first) {
			ret.min_second = ret.min_first;
			ret.min_first = found_dist_min;
		}
		else if (found_dist_min < ret.min_second) {
			ret.min_second = found_dist_min;
		}

		//가장 먼 거리 2개를 저장한다.
		if (ret.max_first < found_dist_max) {
			ret.max_second = ret.max_first;
			ret.max_first = found_dist_max;
		}
		else if (ret.max_second < found_dist_max) {
			ret.max_second = found_dist_max;
		}
	}

	if (path_found) {
		//최소거리와 최대거리가 2개가 저장되어 있다면
		// 즉, 리프 노드가 아니라 중간 노드라면
		//두개의 합을 더해서 갱신
		//ex. A - B - C에서 B 노드일 경우에만 답지를 갱신
		if (ret.max_second != imin) {
			ans_min = min(ans_min, ret.min_first + ret.min_second);
			ans_max = max(ans_max, ret.max_first + ret.max_second);
		}
	}
	//DFS의 끝에 도달했을 경우에는 0을 반환한다
	else {
		ret.max_first = 0;
		ret.max_second = 0;
		ret.min_first = 0;
		ret.min_second = 0;
	}

	return ret;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int p, q, w; cin >> p >> q >> w;
		edges[p].push_back({ q, w });
		edges[q].push_back({ p, w });
	}
	
	ret_val result = DFS(0, -1);
	//만약 출발 노드(0)가 리프 노드였을 경우, 한쪽으로밖에 진행할 수 없으므로
	//한쪽 방향의 값이 결과로 들어올 것이다.
	//이 경우에는 한쪽 방향으로의 값이 최종 답이 된다.
	if (result.max_second == imin) {
		ans_max = max(ans_max, result.max_first);
		ans_min = min(ans_min, result.min_first);
	}

	cout << ans_max << '\n' << ans_min;
}