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
struct cq {

	bool empty() { return size == 0; }
	bool full() { return cap == size; }
	void reserve(int newcap) {
		if (newcap <= cap) { return; }

		T* temp = new T[newcap];
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
		cap = newcap;
		start = 0;
		end = size;
	}
	int next(int cur) { if (++cur >= cap) { cur -= cap; } return cur; }

	void push(const T& t) {
		if (full()) { reserve(cap * 2); }
		cont[end] = t;
		end = next(end);
		++size;
	}
	T top() { return cont[start];}
	void pop() { start = next(start); --size; }

	T* cont{};
	int cap{}, size{}, start{}, end{};
};

int n_node, n_edge, dep, dest;
struct edge { int end, cost; };
std::vector<edge> edges[1001];
cq<int> q;

void djikstra() {
	
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//input
	std::cin >> n_node >> n_edge;
	for (int i = 0; i < n_edge; ++i) {
		int from, to, cost; std::cin >> from >> to >> cost;
		edges[from].push_back({ dep, cost });
	}
	std::cin >> dep >> dest;

	q.reserve(1);
	for (int i = 0; i < 50; ++i) {
		q.push(i);
	}
	for (int i = 0; i < 25; ++i) {
		std::cout << q.top() << '\n'; q.pop();
	}

	for (int i = 0; i < 50; ++i) {
		q.push(i);
	}

	while (false == q.empty()) {
		std::cout << q.top() << '\n'; q.pop();
	}

	
	

	djikstra();

	return 0;
}