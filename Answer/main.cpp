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
using uint = unsigned int;
int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	uint N, M, K; std::cin >> N >> M >> K;
	std::vector<std::vector<uint>> changes(N + 1, std::vector<uint>(M + 1));
	for (uint r = 1; r <= N; ++r) {
		for (uint c = 1; c <= M; ++c) {
			//누적합 계산
			changes[r][c] = changes[r - 1][c] + changes[r][c - 1] - changes[r - 1][c - 1];

			char input; std::cin >> input;
			//'W'로 시작하는 체스판이라고 가정. 'W' == 0
			//(r + c) % 2 -> 현재 체스판에 칠해야 할 색 
			//input == 'B' -> 내 체스판의 색상
			//두 값을 더한 뒤 2로 나누면 -> 색을 바꿔야 하는지 아닌지
			//만약 체스판이 W(0)이고 input이 B라면, (1 + 0) % 2 == 1 -> 색깔을 바꿔야 함.
			//만약 체스판이 B(1)이고 input이 W라면, (0 + 1) % 2 == 1 -> 색깔을 바꿔야 함.
			changes[r][c] += ((uint)(input == 'B') + r + c) % 2u;
		}
	}

	//K * K를 전부 바꿔야 하는 경우(최악)
	const uint changeMax = K * K;
	uint minChange = changeMax;
	for (uint r = N; r >= K; --r) {
		for (uint c = M; c >= K; --c) {
			//인덱스 미리 계산한 경우
			uint rBegin = r - K, cBegin = c - K;
			uint cur = changes[r][c] + changes[rBegin][cBegin] - changes[rBegin][c] - changes[r][cBegin];

			//changeMax - cur == 시작 색깔이 다른 체스판에서의 바꿔야 하는 색의 수
			minChange = std::min(minChange
				, std::min(cur, changeMax - cur)
			);
		}
	}
	std::cout << minChange;

	return 0;
}
