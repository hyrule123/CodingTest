#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 24444 (알고리즘 수업 - 너비 우선 탐색 1)
*/
struct cq {
	void Reserve(int _size) {
		//size만큼을 수용하기 위해서는 size+1 만큼이 필요
		if (++_size <= capacity) { return; }

		int* temp = new int[_size];
		memset(temp, 0, sizeof(int) * _size);
		if (cont) {
			if (start > end) {
				int frontSize = capacity - start;
				memcpy(temp, cont + start, frontSize * sizeof(int));
				memcpy(temp + frontSize, cont, end * sizeof(int));
			}
			else {
				memcpy(temp, cont + start, sizeof(int) * (end - start));
			}
			delete[] cont;

			start = 0;
			end = size;
		}
		cont = temp;
		capacity = _size;
	}

	bool Empty() { return size == 0; }
	bool Full() { return (Next(end) == start); }
	int Next(int _cursor) { if (capacity <= ++_cursor) { _cursor -= capacity; } return _cursor; }
	void PushBack(int _elem) {
		cont[end] = _elem;
		end = Next(end);
		++size;
	}
	int Front() { return cont[start]; }
	void PopFront() { start = Next(start); --size; }

	void PrintAll() {
		int iter = start;
		while (iter != end) {
			std::cout << cont[iter] << '\n';
			iter = Next(iter);
		}
	}

	int* cont = nullptr;
	int size = 0;
	int capacity = 0;
	int start = 0;
	int end = 0;
};

#include <bitset>
#include <vector>
std::vector<int> links[100001];
std::vector<int> temp;
std::bitset<100001> visited;
cq q{};
int N, M, R, ans[100001], ansOrder = 1;
void MergeSort(std::vector<int>& v, int s, int e) {
	if (s >= e) { return; }

	int mid = (s + e) / 2;
	MergeSort(v, s, mid);
	MergeSort(v, mid + 1, e);

	int i = 0;
	int l = s;
	int r = mid + 1;
	while (l <= mid && r <= e) {
		if (v[l] < v[r]) {
			temp[i++] = v[l++];
		}
		else {
			temp[i++] = v[r++];
		}
	}
	for (; l <= mid;) {
		temp[i++] = v[l++];
	}
	for (; r <= e;) {
		temp[i++] = v[r++];
	}

	memcpy(v.data() + s, temp.data(), (e - s + 1) * sizeof(int));
}

void BFS(int r) {
	visited[r] = true;
	ans[r] = ansOrder++;
	q.PushBack(r);
	while (false == q.Empty()) {
		int u = q.Front(); q.PopFront();
		for (int v : links[u]) {
			if (false == visited[v]) {
				visited[v] = true;
				ans[v] = ansOrder++;
				q.PushBack(v);
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	std::cin >> N >> M >> R;
	for (int i = 0; i < M; ++i) {
		int a, b; std::cin >> a >> b;
		links[a].push_back(b);
		links[b].push_back(a);
	}
	for (int i = 1; i <= N; ++i) {
		temp.resize(links[i].size());
		MergeSort(links[i], 0, (int)links[i].size() - 1);
	}
	q.Reserve(N);
	BFS(R);
	for (int i = 1; i <= N; ++i) {
		std::cout << ans[i] << '\n';
	}

	return 0;
}