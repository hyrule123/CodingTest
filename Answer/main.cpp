#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1753 (최단경로)
*/
#include <vector>
template <typename T>
struct minHeap {
	void Insert(T i) {
		cont.push_back(i);
		
		if (cont.size() < 2) { return; }
		size_t cur = cont.size() - 1;
		while (0 < cur) {
			size_t parent = (cur - 1) / 2;

			if (cont[cur] < cont[parent]) {
				std::swap(cont[cur], cont[parent]);
			}
			else {
				break;
			}

			cur = parent;
		}
	}
	T Pop() {
		T ret = cont[0];

		std::swap(cont.front(), cont.back());
		cont.resize(cont.size() - 1);

		if (cont.size() < 2) { return ret; }

		size_t parent = 0;
		size_t end = cont.size() / 2 - 1;
		while (parent <= end) {
			size_t smallest = parent;
			size_t left = smallest * 2 + 1;
			size_t right = left + 1;

			if (left < cont.size() && cont[left] < cont[smallest]) {
				smallest = left;
			}
			if(right < cont.size() && cont[right] < cont[smallest]) {
				smallest = right;
			}

			if (smallest != parent) {
				std::swap(cont[parent], cont[smallest]);
			}
			else {
				break;
			}
			parent = smallest;

		}

		return ret;
	}

	std::vector<T> cont;
};
constexpr int INF = std::numeric_limits<int>::max();
int V, E, K, u, v, w;
#include <array>
struct edge { 
	int to, wt;
	bool operator < (const edge& other) const {
		return wt < other.wt;
	}
};
std::array<std::vector<edge>, 20001> edges;
minHeap<edge> heap;
//K to idx cost
int dp[20001];

void Djikstra() {
	//시작점: K
	heap.Insert({ K, 0 });
	
	while (false == heap.cont.empty()) {
		edge min = heap.Pop();

		//이미 방문했다면 최소거리가 등록된 것이므로 continue
		if (INF != dp[min.to]) {
			continue;
		}

		//방문하지 않았을 경우 최소힙에서 꺼낸 최소 거리이므로 그대로 대입한다.
		dp[min.to] = min.wt;
		
		//heap에서 꺼낸 노드에서 다음 노드로 방문하는 거리를 모조리 등록한다.
		while (false == edges[min.to].empty()) {
			edge next = edges[min.to].back(); edges[min.to].pop_back();
			
			//아직 목적지에 방문하지 않았을 경우 최소힙에 삽입
			if (INF == dp[next.to]) {
				heap.Insert({ next.to, min.wt + next.wt });
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	for (int i = 0; i < 20001; ++i) {
		dp[i] = INF;
	}
	heap.cont.reserve(10000);

	std::cin >> V >> E >> K;
	for (int i = 0; i < E; ++i) {
		std::cin >> u >> v >> w;
		edges[u].push_back({ v, w });
	}
	Djikstra();
	for (int i = 1; i <= V; ++i) {
		if (dp[i] == INF) {
			std::cout << "INF\n";
		}
		else {
			std::cout << dp[i] << '\n';
		}
	}

	return 0;
}