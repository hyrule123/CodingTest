#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 1012 (유기농 배추) - stack 활용
*/
int TC, N, M, K;
#include <bitset>
std::bitset<52> farm[52];
struct coord { int r, c; };
struct stack {
	coord c[500]{};
	int size{};

	bool Empty() { return size == 0; }
	coord Pop() { --size; return c[size]; }
	void Push(coord _coord) { c[size++] = _coord; }
} stk;

void CheckPos(int r, int c) {
	if (farm[r][c]) {
		farm[r][c] = false;
		stk.Push({ r,c });
	}
}

void DFS(int r, int c) {
	CheckPos(r, c);

	//상좌하우 순으로 stack에 넣는다(꺼낼때는 우하좌상 순으로 꺼내짐)
	//재귀 형식일때는 stack에서 뽑을 때 지나갔다고 표시하지만
	//스택일때는 먼저 지나갔다고 표시한 후 stack에 넣어야 한다
	while (false == stk.Empty()) {
		coord c = stk.Pop();

		CheckPos(c.r - 1, c.c);
		CheckPos(c.r, c.c - 1);
		CheckPos(c.r + 1, c.c);
		CheckPos(c.r, c.c + 1);
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> TC;
	while (TC--) {
		std::cin >> N >> M >> K;
		for (int i = 0; i < K; ++i) {
			int r, c; std::cin >> r >> c;
			farm[r + 1][c + 1] = true;
		}

		int ans = 0;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				if (farm[i][j]) {
					++ans;
					DFS(i, j);
				}
			}
		}
		std::cout << ans << '\n';
	}

	return 0;
}