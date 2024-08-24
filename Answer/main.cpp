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

struct edge { int end, cost; };
int n_node, n_edge, dep, dest;
std::vector<edge> edges[1001];
int visited[1001];
pq<int> q;

void djikstra() {
	


}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//input
	memset(visited, -1, sizeof(visited));

	std::cin >> n_node >> n_edge;
	for (int i = 0; i < n_edge; ++i) {
		int from, to, cost; std::cin >> from >> to >> cost;
		edges[from].push_back({ dep, cost });
	}
	std::cin >> dep >> dest;

	for (int i = 100; i > 0; --i) {
		q.Insert(i);
	}
	while (false == q.cont.empty()) {
		std::cout << q.top() << '\n'; q.pop();
	}

	djikstra();

	return 0;
}