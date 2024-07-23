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
	void Insert(const T& i) {
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

			if (left < cont.size() && cont[smallest] > cont[left]) {
				smallest = left;
			}
			if(right < cont.size() && cont[smallest] > cont[right]) {
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
minHeap<int> heap;
int djikstra[20001][20001];

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	srand(time(0));
	for (int i = 1000; i >= 0; --i) {
		heap.Insert(i);
		if (i == 1) {
			int a = 3;
		}
	}
	for (int i = 0; i < 1000; ++i) {
		std::cout << heap.Pop() << '\n';
	}

	return 0;
}