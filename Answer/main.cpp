#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 16928 (뱀과 사다리 게임)
*/
struct pos { int warp = 0, diceCasts = -1; };
pos board[102]{};
#include <vector>
//diceCast가 적은놈을 우선적으로 꺼내줌
struct posInfo { 
	int pos, diceCasts;
};
struct PriorityQueue {
	void Insert(posInfo p) {
		cont.push_back(p);

		int child = (int)cont.size() - 1;
		while(child > 0) {
			int parent = (child - 1) / 2;
			if (cont[child].diceCasts < cont[parent].diceCasts) {
				std::swap(cont[child], cont[parent]);
			}
			else { break; }
			child = parent;
		}
	}
	posInfo Pop() {
		posInfo ret = cont.front();
		std::swap(cont.front(), cont.back());
		cont.resize(cont.size() - 1);

		if (false == cont.empty()) {
			size_t parent = 0;
			size_t end = (cont.size() - 1) / 2;
			while (parent <= end) {
				size_t smallest = parent;
				size_t left = smallest * 2 + 1;
				size_t right = left + 1;
				if (left < cont.size() && cont[left].diceCasts < cont[smallest].diceCasts) {
					smallest = left;
				}
				if (right < cont.size() && cont[right].diceCasts < cont[smallest].diceCasts) {
					smallest = right;
				}
				
				//더이상 내려가지 못하면 break
				if (smallest == parent) { break; }

				std::swap(cont[parent], cont[smallest]);
				parent = smallest;
			}
		}

		return ret;
	}

	std::vector<posInfo> cont;
} q;

int BFS() {
	board[1].diceCasts = 0;
	q.Insert({ 1 , board[1].diceCasts});

	int ret = 0;
	while (false == q.cont.empty()) {
		posInfo cur = q.Pop();
		if (cur.pos == 100) {
			ret = cur.diceCasts;
			break;
		}
		
		//워프가 있다면 워프
		if (board[cur.pos].warp) {
			int warp = board[cur.pos].warp;
			if (-1 == board[warp].diceCasts) {
				board[warp].diceCasts = board[cur.pos].diceCasts;
				q.Insert({warp, board[warp].diceCasts});
			}
		}
		//없으면 주사위 던진다
		else {
			for (int i = 1; i <= 6; ++i) {
				int dest = cur.pos + i;
				if (dest <= 100 && -1 == board[dest].diceCasts) {
					board[dest].diceCasts = board[cur.pos].diceCasts + 1;
					q.Insert({ dest, board[dest].diceCasts });
				}
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
	while (ladder--) {
		int from, to; std::cin >> from >> to;
		board[from].warp = to;
	}
	while (snake--) {
		int from, to; std::cin >> from >> to;
		board[from].warp = to;
	}
	q.cont.reserve(100);
	std::cout << BFS();

	return 0;
}