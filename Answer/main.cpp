#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 2178 (미로 탐색)
*/
struct coord { int x, y; };
struct CircleQueue {
	bool Empty() { return size == 0; }
	bool Full() { return capacity == size + 1; }
	int Next(int i) { if (++i >= capacity) { i -= capacity; } return i; }
	void Reserve(int cap) {
		if (++cap <= capacity) { return; }

		coord* temp = new coord[cap];
		memset(temp, 0, sizeof(coord) * cap);
		if (cont) {
			if (end < start) {
				int frontSize = capacity - start;
				memcpy(temp, cont + start, sizeof(coord) * frontSize);
				memcpy(temp + frontSize, cont, sizeof(coord) * end);
			}
			else {
				memcpy(temp, cont + start, sizeof(coord) * (end - start + 1));
			}
			start = 0;
			end = size;

			delete[] cont;
		}
		cont = temp;
		capacity = cap;
	}
	void PushBack(int x, int y) {
		if (Full()) {
			Reserve(size * 2);
		}

		cont[end] = { x, y };
		end = Next(end);
		++size;
	}
	void PopFront() { start = Next(start); --size; }
	coord Front() { return cont[start]; }
 
	coord* cont{};
	int size{}, capacity{}, start{}, end{};
} q;

#include <array>
#define WALL -1
#define PATH -2
//길 주변에 벽을 둘러줄예정 -> 둘레를 1씩 추가한다
using Map = std::array<std::array<int, 102>, 102>;
constexpr Map Fill() {
	Map m;
	for (int i = 0; i < 102; ++i) {
		m[i].fill(WALL);
	}
	return m;
}
//기본 WALL(-1)로 채워놓는다
Map map = Fill();
int N, M;

int BFS() {
	//1,1부터 시작이므로 0
	map[1][1] = 0;
	q.PushBack(1, 1);

	int ret = 0;
	while (false == q.Empty()) {
		coord c = q.Front(); q.PopFront();

		//도착했을 경우 거리를 반환
		if (c.x == N && c.y == M) { 
			ret = map[c.x][c.y] + 1; break; 
		}
		
		//지나갈 수 있는 길일 경우 그 자리에 여태까지 걸어온 거리를 기록
		if (map[c.x][c.y + 1] == PATH) {
			map[c.x][c.y + 1] = map[c.x][c.y] + 1;
			q.PushBack(c.x, c.y + 1);
		}
		if (map[c.x + 1][c.y] == PATH) {
			map[c.x + 1][c.y] = map[c.x][c.y] + 1;
			q.PushBack(c.x + 1, c.y);
		}
		if (map[c.x][c.y - 1] == PATH) {
			map[c.x][c.y - 1] = map[c.x][c.y] + 1;
			q.PushBack(c.x, c.y - 1);
		}
		if (map[c.x - 1][c.y] == PATH) {
			map[c.x - 1][c.y] = map[c.x][c.y] + 1;
			q.PushBack(c.x - 1, c.y);
		}
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> M;

	for (int r = 1; r <= N; ++r) {
		char input[101]; std::cin >> input;
		for (int c = 1; c <= M; ++c) {
			//지나갈수 있는 길은 PATH(-2)로 채워준다
			if (input[c - 1] == '1') { map[r][c] = PATH; }
		}
	}

	q.Reserve(1000);
	std::cout << BFS();

	return 0;
}