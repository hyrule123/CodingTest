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

	uint N, M, K; std::cin >> N >> M >> K;
	std::vector<std::vector<char>> bw(N, std::vector<char>(M));
	std::vector<std::vector<uint>> board(N + 2, std::vector<uint>(M + 2));

	std::cin.getline(bw[2].data() + 2, M);
	for (uint r = 2; r <= N + 1; ++r) {
		for (uint c = 2; c <= M + 1; ++c) {
			uint& cur = board[r][c];
			cur = board[r-2][c]+board[r][c-2]-board[r-2][c-2];
			if (bw[r - 1][c - 1] == 'B') { ++cur; };

			std::cin >> bw[r][c];
			if (bw[r][c] == 'B') { ++cur; }
		}
	}

	return 0;
}
