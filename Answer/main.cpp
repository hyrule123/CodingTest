#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 24479 (알고리즘 수업 - 깊이 우선 탐색 1)
*/
#include <bitset>
#include <array>
std::array<std::bitset<100001>, 100001> links;
struct link { 
	int from, to; 
	bool operator < (const link& _other) const {
		if (from == _other.from) {
			return to < _other.to;
		}
		return from < _other.from;
	}
};
link links[200000]{};
int N, M, R, size = 0, nodes[100001]{};

void Heapify(int _parent, int _size) {
	int max = _parent;
	int left = max * 2 + 1;
	int right = left + 1;

	if (left < _size && links[max] < links[left]) {
		max = left;
	}
	if (right < _size && links[max] < links[right]) {
		max = right;
	}

	if (max != _parent) {
		std::swap(links[max], links[_parent]);

		Heapify(max, _size);
	}
}
void HeapSort() {
	for (int i = M - 1; i >= 1; --i) {
		std::swap(links[0], links[i]);
		Heapify(0, i);
	}
}

void HeapifyUp() {
	int child = size - 1;

	while (0 < child) {
		int parent = (child - 1) / 2;
		if (links[parent] < links[child]) {
			std::swap(links[parent], links[child]);
		}
		child = parent;
	}
}

void DFS(int node, int linkIdxStart, int linkIdxEnd) {
	if (node > N) { return; }
	++(nodes[node]);

	int nextIdxEnd = linkIdxEnd;

	while (linkIdxStart <= linkIdxEnd) {
		DFS(links[linkIdxStart].to, linkIdxEnd + 1);
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> M >> R;
	for (int i = 0; i < N; ++i) {
		std::cin >> links[size].from >> links[size].to; ++size;
		HeapifyUp();
	}
	HeapSort();



	return 0;
}