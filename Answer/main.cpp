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
using uint = std::uint32_t;

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	uint N, M; std::cin >> N >> M;
	std::vector<std::vector<uint>> board(N + 1, std::vector<uint>(N + 1));

	for (uint r = 1; r <= N; ++r) {
		for (uint c = 1; c <= N; ++c) {
			uint& cur = board[r][c];
			std::cin >> cur;
			cur += board[r - 1][c] + board[r][c - 1] - board[r - 1][c - 1];
		}
	}

	for (uint i = 1; i <= M; ++i) {
		uint x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2;

		//구하는 블록까지의 전체합 - 블록 윗줄까지의 합 - 블록 왼쪽까지의 합 + 윗줄 옆줄 겹치는 부분의 합
		std::cout << board[x2][y2] - board[x1 - 1][y2] - board[x2][y1 - 1] + board[x1 - 1][y1 - 1] << '\n';
	}

	return 0;
}
