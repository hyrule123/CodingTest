#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
constexpr const bool blackPattern[2][2] = { {true, false}, {false, true} };
//true==black false==white
inline bool IsBlack(int _r, int _c) {
	return blackPattern[_r % 2][_c % 2];
}

//검은색/흰색으로 시작하는 보드에서 각각 색칠해야 하는 칸의 수를 기록
struct changeCount { 
	int blackStart, whiteStart; 
	changeCount operator+(const changeCount& _o) {
		return changeCount{ blackStart + _o.blackStart, whiteStart + _o.whiteStart };
	}
	changeCount operator-(const changeCount& _o) {
		return changeCount{ blackStart - _o.blackStart , whiteStart - _o.whiteStart };
	}
};

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	int N, M, K; std::cin >> N >> M >> K;
	std::vector<std::vector<changeCount>> board(N + 1, std::vector<changeCount>(M + 1));

	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= M; ++c) {
			changeCount& cur = board[r][c];
			int prevR = r - 1, prevC = c - 1;

			cur = board[prevR][c] + board[r][prevC] - board[prevR][prevC];

			char input; std::cin >> input;

			//내 체스판이 B인데
			if (input == 'B') {
				//검은색을 칠해야 한다->검은색 체스판기준 맞음, 흰색 체스판기준 틀림
				if (IsBlack(r, c)) {
					++cur.whiteStart;
				}
				//흰색을 칠해야 한다-> 검은색 체스판 기준 틀림, 흰색 체스판기준 맞음
				else {
					++cur.blackStart;
				}
			}
			else {//내 체스판이 W인데
				//검은색을 칠해야 한다->검은색 체스판기준 틀림, 흰색 체스판기준 맞음
				if (IsBlack(r, c)) {
					++cur.blackStart;
				}
				//검은색을 칠해야 한다->검은색 체스판기준 맞음, 흰색 체스판기준 틀림
				else {
					++cur.whiteStart;
				}
			}
		}
	}

	int minChangesCount = std::numeric_limits<int>::max();
	for (int r = 1, rEnd = N - K + 1; r <= rEnd; ++r) {
		for (int c = 1, cEnd = M - K + 1; c <= cEnd; ++c) {
			int r1 = r - 1, c1 = c - 1;
			int r2 = r1 + K, c2 = c1 + K;

			changeCount counts = board[r2][c2] + board[r1][c1] - board[r1][c2] - board[r2][c1];

			minChangesCount = std::min(minChangesCount, std::min(counts.blackStart, counts.whiteStart));
		}
	}
	std::cout << minChangesCount;

	return 0;
}
