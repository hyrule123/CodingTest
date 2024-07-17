#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 1697 (숨바꼭질)
*/
struct Coord { 
	int r, c;
	Coord operator + (const Coord& _other) const {
		return { r + _other.r, c + _other.c };
	}
	bool Inbound(int size) {
		return (0 <= r && 0 <= c && r < size && c < size);
	}
};
constexpr Coord dirs[] = {
	{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}
};
struct CircleQueue {
	void Reserve(int _cap) {
		if (capacity >= _cap) { return; }

		Coord* temp = new Coord[_cap];
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
		cont = temp;
		start = 0;
		end = size;
		capacity = _cap;
	}

	bool Empty() { return size == 0; }
	bool Full() { return size == capacity; }
	int Next(int cur) { if (++cur >= capacity) { cur -= capacity; } return cur; }
	void Clear() { size = 0; start = 0; end = 0; }

	void PushBack(Coord i) { 
		if (Full()) { Reserve(capacity * 2); }
		cont[end] = i; end = Next(end); ++size; }
	Coord PopFront() { Coord ret = cont[start]; start = Next(start); --size; return ret; }

	Coord* cont{};
	int capacity{}, size{}, start{}, end{};
} q;

#include <array>
std::array<std::array<int, 300>, 300> board;
#define NOT_VISITED -1
int BFS() {
	int size; Coord from, to;
	std::cin>> size >> from.r >> from.c >> to.r >> to.c;
	for (int i = 0; i < size; ++i) {
		board[i].fill(NOT_VISITED);
	}
	board[from.r][from.c] = 0;
	q.Clear();
	q.Reserve(size);
	q.PushBack(from);

	int ret = 0;
	while (false == q.Empty()) {
		Coord cur = q.PopFront();
		if (cur.r == to.r && cur.c == to.c) {
			ret = board[cur.r][cur.c]; break;
		}

		for (int dir = 0; dir < 8; ++dir) {
			Coord next = cur + dirs[dir];
			if (
				next.Inbound(size) 
				&& NOT_VISITED == board[next.r][next.c]) {
				board[next.r][next.c] = board[cur.r][cur.c] + 1;
				q.PushBack(next);
			}
		}
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int tc; std::cin >> tc;
	while (tc--) {
		std::cout << BFS() << '\n';
	}

	return 0;
}