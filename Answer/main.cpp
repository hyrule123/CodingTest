#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 11779 (최소비용 구하기 2)
*/
#include <vector>
#include <stack>

template <typename T>
struct pq {
	void Insert(const T& t) {
		cont.push_back(t);

		size_t cur = cont.size() - 1;
		while (0 < cur) {
			size_t parent = (cur - 1) / 2;

			if (cont[cur] < cont[parent]) {
				std::swap(cont[parent], cont[cur]);
				cur = parent;
			}
			else {
				break;
			}
		}
	}

	T top() { return cont.front(); }
	void pop() {
		std::swap(cont.front(), cont.back());
		
		cont.resize(cont.size() - 1);
		if (cont.empty()) { return; }

		size_t cur = 0;
		size_t end = cont.size() / 2;
		while (cur < end) {
			size_t min_idx = cur;
			size_t left = cur * 2 + 1;
			size_t right = left + 1;

			if (left < cont.size() && cont[left] < cont[min_idx]) {
				min_idx = left;
			}
			if (right < cont.size() && cont[right] < cont[min_idx]) {
				min_idx = right;
			}

			if (cur != min_idx) {
				std::swap(cont[cur], cont[min_idx]);
				cur = min_idx;
			}
			else {
				break;
			}
		}
	}

	std::vector<T> cont;
};

struct edge { 
	int to, cost;
};
struct trace_log {
	int prev = 0, dist = -1;
};
struct travel {
	int from, to, dist;
	bool operator < (const travel& other) const {
		return dist < other.dist;
	}
};

int n_node, n_edge, dep, dest;
std::vector<edge> edges[1001];
trace_log visited[1001];
pq<travel> q;

void djikstra() {
	q.Insert({ dep, dep, 0 });

	while (false == q.cont.empty()) {
		//우선순위 큐로부터 현재 가장 짧은 간선을 반환받는다
		travel cur = q.top(); q.pop();

		if (visited[cur.to].dist != -1) { continue; }

		visited[cur.to].prev = cur.from;
		visited[cur.to].dist = cur.dist;

		if (cur.to == dest) {
			break;
		}
		
		//이번 노드에 연결왼 간선들을 우선순위 큐에 넣는다.
		travel next;
		next.from = cur.to;
		for (const auto& e : edges[cur.to]) {
			if (visited[e.to].dist == -1) {
				next.to = e.to;
				next.dist = cur.dist + e.cost;
				q.Insert(next);
			}
		}
	}
}

void trace_back() {
	//거리 출력
	std::cout << visited[dest].dist << '\n';

	int cur = dest;
	int count = 0;
	std::stack<int> ans;
	while (true) {
		ans.push(cur);
		++count;

		if (cur == dep) {
			break;
		}

		cur = visited[cur].prev;
	}

	//거쳐가는 도시 갯수 출력
	std::cout << count << '\n';

	//거쳐가는 도시들 나열
	while (false == ans.empty()) {
		std::cout << ans.top() << ' '; ans.pop();
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//input
	memset(visited, -1, sizeof(visited));

	std::cin >> n_node >> n_edge;
	for (int i = 0; i < n_edge; ++i) {
		int from, to, cost; std::cin >> from >> to >> cost;
		edges[from].push_back({ to, cost });
	}
	std::cin >> dep >> dest;

	djikstra();
	trace_back();

	return 0;
}