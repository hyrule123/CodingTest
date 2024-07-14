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
std::bitset<100001> visited;
cq q{};
int N, M, R, ans[100001];

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	std::cin >> N >> M >> R;
	
	srand(time(0));
	int s = rand() % 100;
	q.Reserve(s);
	for (int i = 0; i < s / 2; ++i) {
		q.PushBack(rand());
		q.PopFront();
	}
	for (int i = 0; i < s; ++i) {
		q.PushBack(rand());
	}
	q.PrintAll();
	s = rand() % 100 + 100;
	q.Reserve(s);
	std::cout << '\n';
	q.PrintAll();

	return 0;
}