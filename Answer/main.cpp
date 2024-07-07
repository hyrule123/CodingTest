#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <array>
using uint = unsigned int;
enum dir { left, up, right, down };

uint N, M;
uint path[502][502];
uint memo[502][502];	//memo: x, y에서 N, M까지 갈 수 있는 방법의 수

uint Recursive(uint x, uint y) {

	//도착했을 경우 1을 return
	if (x == N && y == M) { return 1; }

	//아직 지나가지 않은 길일 경우 탐색
	else if (0xff'ff'ff'ff == memo[x][y]) {
		memo[x][y] = 0;

		if (path[x - 1][y] < path[x][y]) { memo[x][y] += Recursive(x - 1, y); }
		if (path[x][y - 1] < path[x][y]) { memo[x][y] += Recursive(x, y - 1); }
		if (path[x + 1][y] < path[x][y]) { memo[x][y] += Recursive(x + 1, y); }
		if (path[x][y + 1] < path[x][y]) { memo[x][y] += Recursive(x, y + 1); }
	}

	//이미 지나간 길일 경우 memo를 반환
	return memo[x][y];
}


int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> M;
	memset(path, 0xff, sizeof(uint) * 502 * 502);
	memset(memo, 0xff, sizeof(uint) * 502 * 502);
	for (uint r = 1; r <= N; ++r) {
		for (uint c = 1; c <= M; ++c) {
			std::cin >> path[r][c];
		}
	}

	std::cout << Recursive(1, 1);

	return 0;
}