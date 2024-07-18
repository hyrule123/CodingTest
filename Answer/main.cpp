#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 16928 (뱀과 사다리 게임)
*/
struct CircleQueue {
	bool Empty() { return 0 == size; }
	bool Full() { return capacity == size; }
	int Next(int cur) { if (++cur >= capacity) { cur -= capacity; } return cur; }

	void Reserve(int cap) {
		if (cap <= capacity) { return; }

		int* temp = new int[cap];
		if (cont) {
			if (false == Empty()) {
				if (start < end) {
					memcpy(temp, cont + start, sizeof(int) * size);
				}
				else {
					int startPartSize = capacity - start;
					memcpy(temp, cont + start, sizeof(int) * startPartSize);
					memcpy(temp + startPartSize, cont, sizeof(int) * end);
				}
			}
			delete[] cont;
		}
		cont = temp;
		start = 0;
		end = size;
		capacity = cap;
	}

	void PushBack(int i) {
		if (Full()) { Reserve(capacity * 2); }
		cont[end] = i;
		end = Next(end);
		++size;
	}
	int PopFront() {
		int ret = cont[start];
		start = Next(start); --size;
		return ret;
	}

	int* cont{}, capacity{}, size{}, start{}, end{};
} q;
struct pos {
	int diceCasts = -1;
	int warp = 0;
};
pos board[102]{};
int BFS() {
	board[1].diceCasts = 0;
	q.PushBack(1);

	int ret = 0;
	while (false == q.Empty()) {
		int cur = q.PopFront();
		int diceCasted = board[cur].diceCasts;
		if (cur == 100) {
			ret = diceCasted;
			break;
		}
		
		//워프가 있다면 워프한 곳 기준에서 주사위를 던진다(주사위를 던지지 않으므로 경우의 수에 합산하지 않음)
		if (board[cur].warp) {
			cur = board[cur].warp;
		}

		for (int i = 1; i <= 6; ++i) {
			int dest = cur + i;
			if (dest <= 100 && -1 == board[dest].diceCasts) {
				board[dest].diceCasts = diceCasted + 1;
				q.PushBack(dest);
			}
		}
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//어차피 둘다 특정위치로 이동시키는건 똑같음
	int ladder, snake; std::cin >> ladder >> snake;
	for (int i = 0; i < ladder + snake; ++i) {
		int from, to; std::cin >> from >> to;
		board[from].warp = to;
	}
	q.Reserve(100);
	std::cout << BFS();

	return 0;
}