#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 2206 (벽 부수고 이동하기)
*/
int R, C;
struct Coord {
	int r, c;
	bool wallDestroyed = false;
	Coord operator + (const Coord& other) {
		return { r + other.r, c + other.c, wallDestroyed || other.wallDestroyed };
	}
	bool Inbound() {
		return (1 <= r && 1 <= c && r <= R && c <= C);
	}
};
struct CircleQueue {
	bool Empty() { return size == 0; }
	bool Full() { return size == capacity; }
	int Next(int cur) { if (++cur >= capacity) { cur -= capacity; } return cur; }
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

		cont = temp;
		capacity = cap;
		start = 0;
		end = size;
	}
	void PushBack(Coord c) {
		if (Full()) { Reserve(capacity * 2); }
		cont[end] = c;
		end = Next(end);
		++size;
	}
	Coord PopFront() {
		Coord ret = cont[start];
		start = Next(start);
		--size;
		return ret;
	}

	Coord* cont;
	int capacity, size, start, end;
} q{};

//마지막 인덱스: 벽 파괴 찬스 사용여부
bool map[1001][1001][2];
int ans[1001][1001][2];
char input[1001];
#define CHANCE_AVBL false
#define CHANCE_USED true
#define WALL true
#define PATH false
constexpr Coord dirs[] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

//애매했던 것들
//1. 벽은 1회만 부술 수 있다.
//2. 벽을 뚫고 간 다음, 다시 상하좌우 이동이 가능하다(벽 넘어서 다음칸이 아니다)
//3. 벽을 뚫은것도 1회 이동이다.

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> R >> C;
	q.Reserve(1024);
	for (int r = 1; r <= R; ++r) {
		std::cin >> input;
		for (int c = 1; c <= C; ++c) {
			if (input[c - 1] == '1') {
				map[r][c][CHANCE_AVBL] = WALL;
				map[r][c][CHANCE_USED] = WALL;
			}
		}
	}
	map[1][1][CHANCE_AVBL] = map[1][1][CHANCE_USED] = WALL;
	map[R][C][CHANCE_AVBL] = map[R][C][CHANCE_USED] = PATH;

	ans[1][1][CHANCE_AVBL] = ans[1][1][CHANCE_USED] = 1;
	q.PushBack({ 1, 1, CHANCE_AVBL });

	bool arrivals[2] = { false, false };
	int answer = std::numeric_limits<int>::max();
	while (false == q.Empty()) {
		Coord cur = q.PopFront();

		//도착 확인. 둘다 도착시 루프 종료
		if (arrivals[CHANCE_AVBL] && arrivals[CHANCE_USED]) { break; }
		else if (cur.r == R && cur.c == C) { 
			arrivals[cur.wallDestroyed] = true;
			answer = std::min(answer, ans[cur.r][cur.c][cur.wallDestroyed]);
			continue; 
		}

		for (int dir = 0; dir < 4; ++dir) {
			//다음 목적지 좌표를 계산한다. 범위 바깥일 시 스킵
			Coord next = cur + dirs[dir];
			if (false == next.Inbound()) { continue; }

			//지나갈 수 있는 길일 경우: 지나간다
			//벽 파괴 찬스 사용상태를 유지(+ operator예서 합산됨)
			if (PATH == map[next.r][next.c][next.wallDestroyed]) {
				map[next.r][next.c][next.wallDestroyed] = WALL;
				ans[next.r][next.c][next.wallDestroyed] = ans[cur.r][cur.c][cur.wallDestroyed] + 1;
				q.PushBack(next);
			}

			//벽일 경우 1회에 한하여 벽을 부술수 있다.
			else if (false == cur.wallDestroyed && WALL == map[next.r][next.c][next.wallDestroyed]) {
				//벽을 부쉈다고 표시 후 벽의 위치를 큐에 삽입
				next.wallDestroyed = true;
				ans[next.r][next.c][next.wallDestroyed] = ans[cur.r][cur.c][cur.wallDestroyed] + 1;
				q.PushBack(next);
			}
		}
	}

	//둘다 접근해본적이 없으면 -1 출력
	std::cout << (std::numeric_limits<int>::max() == answer ? -1 : answer);

	return 0;
}