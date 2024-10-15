#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() { 
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

//Prim Algorithm 사용
#include <vector>
#include <queue>

struct edge {
	int dest, cost;
	auto operator < (const edge& other) const {
		//부호를 반대로 줬음(Priority queue)
		return this->cost > other.cost;
	}
};
std::vector<std::vector<edge>> graph;

int MST_Prim() {
	std::priority_queue<edge> pq;
	std::vector<bool> visited;
	visited.resize(graph.size(), false);
	int cost = 0;

	visited[0] = true;
	for (const auto& e : graph[0]) {
		pq.push({ e.dest, e.cost });
	}

	//종료조건: n-1개의 간선 연결
	const int end_cond = (int)graph.size() - 1;
	int edges_count = 0;
	while (false == pq.empty() && edges_count < end_cond) {
		edge e = pq.top(); pq.pop();

		if (visited[e.dest]) { continue; }
		
		visited[e.dest] = true;//방문하지 않았을 경우 연결
		++edges_count;//연결 카운트 ++
		cost += e.cost;//비용 합산
		for (const auto& next_e : graph[e.dest]) {
			pq.push({ next_e.dest, next_e.cost });
		}
	}

	return cost;
}

void solve()
{
	while (true) {
		int m, n, total_cost = 0;
		std::cin >> m >> n;
		if (m == 0 && n == 0) { break; }

		graph.clear();
		graph.resize(m);
		
		for (int i = 0; i < n; ++i) {
			int a, b, cost; std::cin >> a >> b >> cost;
			graph[a].push_back({ b, cost });
			graph[b].push_back({ a, cost });
			total_cost += cost;
		}

		int min_cost = MST_Prim();
		//총비용에서 빼준다
		std::cout << total_cost - min_cost << '\n';
	}

}
