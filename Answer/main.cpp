#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 7576 (토마토)
*/
int R, C;
struct Coord { int r, c; };
struct CircleQueue {
	bool Empty() { return size == 0; }
	bool Full() { return size == capacity; }
	int Next(int cur) { if (++cur >= capacity) { cur -= capacity; } return cur; }
	void PushBack(Coord c) { 
		if (Full()) { Reserve(capacity * 2); } 
		cont[end] = c; 
		end = Next(end); 
		++size; 
	}
	Coord PopFront() { Coord ret = cont[start]; start = Next(start); --size; return ret; }
	void Reserve(int cap) {
		if (cap <= capacity) { return; }

		Coord* temp = new Coord[cap];
		if (cont) {
			if (false == Empty()) {
				if (start < end) {
					memcpy(temp, cont + start, sizeof(Coord) * size);
				}
				else {
					int startPartSize = capacity - start;
					memcpy(temp, cont + start, sizeof(Coord) * startPartSize);
					memcpy(temp + startPartSize, cont, sizeof(Coord) * end);
				}
			}
			delete[] cont;
		}
		start = 0;
		end = size;
		capacity = cap;
		cont = temp;
	}

	Coord* cont{};
	int capacity{}, size{}, start{}, end{};
} q;

int farm[1002][1002]{};
void Check(int r, int c, Coord orig) {
	if (farm[r][c] == 0) {
		farm[r][c] = farm[orig.r][orig.c] + 1;
		q.PushBack({ r, c });
	}
}

int BFS() {
	Coord last{};
	while (false == q.Empty()) {
		last = q.PopFront();
		
		Check(last.r, last.c - 1, last);
		Check(last.r, last.c + 1, last);
		Check(last.r - 1, last.c, last);
		Check(last.r + 1, last.c, last);
	}

	return farm[last.r][last.c] - 1;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> C >> R;
	//BFS 탐색을 해야하는 범위 주변으로 -1을 둘러쳐 준다.
	for (int r = 0; r <= R + 1; ++r) {
		farm[r][0] = -1;
		farm[r][C + 1] = -1;
	}
	for (int c = 0; c <= C + 1; ++c) {
		farm[0][c] = -1;
		farm[R + 1][c] = -1;
	}

	q.Reserve(std::max(R, C));
	for (int r = 1; r <= R; ++r) {
		for (int c = 1; c <= C; ++c) {
			std::cin >> farm[r][c];
			if (1 == farm[r][c]) {
				q.PushBack({ r, c });
			}
		}
	}
	int days = BFS();

	//혹시나 안 익은 토마토(0)이 남아있을 경우 -1을 출력하고 프로그램 종료
	for (int r = 1; r <= R; ++r) {
		for (int c = 1; c <= C; ++c) {
			if (0 == farm[r][c]) {
				std::cout << -1;
				return 0;
			}
		}
	}
	std::cout << days;

	return 0;
}