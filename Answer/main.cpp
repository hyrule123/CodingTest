#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

#include <vector>
#include <algorithm>
#include <cmath>

template <typename T>
struct priority_queue {
	priority_queue(int _cap) : cap(_cap), size(0) { q = new T[_cap]; }
	~priority_queue() { if (q) { delete[] q; } }

	void insert(const T& t) {
		q[size] = t;
		int cur = size;
		++size;

		int parent = (cur - 1) / 2;
		while (0 <= parent) {
			if (q[cur] < q[parent]) {
				std::swap(q[cur], q[parent]);
				cur = parent;
				parent = (cur - 1) / 2;
			}
			else {
				break;
			}
		}
	}

	T pop() {
		T ret = q[0];

		if (0 < size) {
			std::swap(q[0], q[--size]);
		}

		build_heap();

		return ret;
	}

	void build_heap() {
		int parent = 0;

		while (parent < size) {
			int left = parent * 2 + 1, right = left + 1, smallest = parent;

			if (left < size && q[left] < q[smallest]) {
				smallest = left;
			}
			if (right < size && q[right] < q[smallest]) {
				smallest = right;
			}

			if (parent != smallest) {
				std::swap(q[parent], q[smallest]);
				parent = smallest;
			}
			else {
				break;
			}
		}
	}

	void clear() {
		size = 0;
	}
	bool empty() { return size == 0; }

	T* q;
	int cap, size;
};

struct coord {
	float x, y;
	coord operator-(const coord& other) {
		return { this->x - other.x, this->y - other.y };
	}

	float length(const coord& other) {
		coord dist = *this - other;
		return std::sqrt(dist.x * dist.x + dist.y * dist.y);
	}
};

struct edge {
	float dist;
	int dest;
	bool operator < (const edge& other) const {
		return this->dist < other.dist;
	}
};

int n;
std::vector<coord> nodes;
std::vector<bool> visited;

float Prim_MST() {
	float ret = 0;
	priority_queue<edge> pq(10000);
	int edge_count = 0;

	visited[0] = true;

	//0번에서 갈 수 있는 간선을 전부 계산해서 PQ에 넣어준다
	for (int i = 1; i < (int)nodes.size(); ++i) {
		pq.insert({ nodes[0].length(nodes[i]), i });
	}

	//edge_count가 n-1에 도달하면 Spanning Tree가 만들어진거임
	while (edge_count < n - 1) {
		edge e = pq.pop();

		if (visited[e.dest]) { continue; }

		//방문 처리하고 해당 간선 길이를 추가
		visited[e.dest] = true;
		ret += e.dist;
		++edge_count;

		//해당 노드에서 이동할 수 있는 간선을 추가(이미 방문했던 노드는 제외)
		for (int i = 0; i < (int)nodes.size(); ++i) {
			if (visited[i]) { continue; }
			pq.insert({ nodes[e.dest].length(nodes[i]), i });
		}
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> n;
	nodes.resize(n);
	visited.resize(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> nodes[i].x >> nodes[i].y;
	}

	std::cout << Prim_MST();

	return 0;
}