#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 11780 (플로이드 2)
*/
/*
* 플로이드 개념: dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
* 저장된 i~j 거리와 k를 경유해서 오는 거리를 비교

* 역추적: 플로이드-와샬 알고리즘의 경우 i~j 노드를 중간 경유지 k를 통해 오는게 더 빠를 경우 값을 갱신한다.
* 이 때, 중간 경유지 i~k 사이에 중간 경유지가 또 있을 수 있다.(l)
* 그럼 i~l~k가 되고, 각각의 경유지 사이에 또 경유지가 있을 수 있다(재귀 형태)
* 모든 중간 경유지를 합산해서 출력하면 그게 경로가 된다.
*/
#include <vector>
constexpr int INF = (int)1e5 + 10;

template <typename T>
struct CQ {
	bool empty() { return size == 0; }
	bool full() { return size == cap; }
	void resize(int _cap) {		
		T* temp = new T[_cap];
		if (cont) {
			if (false == empty()) {
				if (start < end) {
					memcpy(temp, cont + start, sizeof(T) * size);
				}
				else {
					int start_part_size = cap - start;
					memcpy(temp, cont + start, sizeof(T) * start_part_size);
					memcpy(temp + start_part_size, cont, sizeof(T) * end);
				}
			}

			delete[] cont;
		}

		cont = temp;
		cap = _cap;
		start = 0;
		end = size;
	}

	int next(int i) { if (++i >= cap) { i -= cap; } return i; }
	void push(T t) {
		if (full()) { resize(cap * 2); }
		cont[end] = t;
		end = next(end);
		++size;
	}
	T pop() {
		T ret = cont[start];
		start = next(start);
		--size;
		return ret;
	}

	T* cont{};
	int size{}, cap{}, start{}, end{};
};
struct edge {
	int dist = INF, stop_over = INF;
};

int n_nodes, n_edges;
edge memo[101][101];
CQ<int> ans;

void floyd() {
	for (int stop_over = 1; stop_over <= n_nodes; ++stop_over) {
		for (int from = 1; from <= n_nodes; ++from) {
			for (int to = 1; to <= n_nodes; ++to) {
				int acc_dist = memo[from][stop_over].dist + memo[stop_over][to].dist;
				if (acc_dist < memo[from][to].dist) {
					memo[from][to].dist = acc_dist;
					//역추적을 위해 값이 저장될 경유 중간 경유지도 저장한다.
					memo[from][to].stop_over = stop_over;
				}
			}
		}
	}

	for (int i = 1; i <= n_nodes; ++i) {
		for (int j = 1; j <= n_nodes; ++j) {
			//답 1: i~j 최단경로를 출력
			int output = memo[i][j].dist == INF ? 0 : memo[i][j].dist;
			std::cout << output << ' ';
		}
		std::cout << '\n';
	}
}

//DFS 형태로 앞쪽부터 기록
void trace_back_recursive(int from, int to) {
	int stopover = memo[from][to].stop_over;
	
	if (stopover != INF) {
		trace_back_recursive(from, stopover);
		ans.push(stopover);
		trace_back_recursive(stopover, to);
	}
}

//답 2: i~j 최단경로를 지날 때 지나가는 노드 갯수와 노드를 출력
void trace_back() {
	for (int i = 1; i <= n_nodes; ++i) {
		for (int j = 1; j <= n_nodes; ++j) {
			if (i == j || memo[i][j].dist == INF) {
				std::cout << 0 << '\n';
				continue;
			}
			
			ans.push(i);
			//stopover을 싹 모은다
			trace_back_recursive(i, j);
			ans.push(j);
			
			std::cout << ans.size << ' ';
			while (false == ans.empty()) {
				std::cout << ans.pop() << ' ';
			}
			std::cout << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	ans.resize(100);
	std::cin >> n_nodes >> n_edges;
	for (int i = 1; i <= n_nodes; ++i) {
		memo[i][i].dist = 0;
	}
	for (int i = 1; i <= n_edges; ++i) {
		int from, to, cost; std::cin >> from >> to >> cost;

		//출발점, 도착점이 같고 거리만 다른 간선이 여러개 있음.
		memo[from][to].dist = std::min(memo[from][to].dist, cost);
	}

	floyd();
	trace_back();

	return 0;
}