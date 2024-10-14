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
	priority_queue(size_t _cap): cap(_cap), size(0) { q = new T[_cap]; }
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

struct coord{
	float x, y;
	coord operator-(const coord& other) {
		return { this->x - other.x, this->y - other.y };
	}

	float lengthsquared(const coord& other) {
		coord dist = *this - other;
		return dist.x * dist.x + dist.y * dist.y;
	}
};
struct edge {
	float cost_squared, a, b;
};
struct set_info {
	int parent, rank;
};

int n;
std::vector<coord> nodes;
std::vector<bool> visited;

float prim_MST() {
	float ret = 0;
	priority_queue<float> pq(10000);
	int edge_count = 0;

	visited[0] = true;

	for (size_t i = 1; i < nodes.size(); ++i) {
		pq.insert(nodes[0].lengthsquared(nodes[i]));
	}

	while (edge_count != n - 1) {
		pq.pop();
	}


	for (size_t i = 0; i < nodes.size(); ++i) {
		for (size_t j = i + 1; j < nodes.size(); ++j) {
			if (visited[j]) { continue; }

			pq.insert(nodes[i].lengthsquared(nodes[j]));
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

	priority_queue<int> iq(100);
	for (int i = 99; i >= 0; --i) {
		iq.insert(i);
	}
	while (false == iq.empty()) {
		std::cout << iq.pop() << '\n';
	}
	

	return 0;
}