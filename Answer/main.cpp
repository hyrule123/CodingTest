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

	size_t N{}; std::cin >> N;
	std::vector<uint> scores(N);
	std::vector<uint> maxScores(N);

	std::cin >> scores[0];
	maxScores[0] = scores[0];

	if (N == 1) { std::cout << maxScores[0]; return 0; }

	std::cin >> scores[1];
	maxScores[1] = scores[0] + scores[1];

	if (N == 2) { std::cout << maxScores[1]; return 0; }

	std::cin >> scores[2];
	maxScores[2] = std::max(scores[0], scores[1]) + scores[2];
	//먹 + 이번꺼 안먹
	maxScores[2] = std::max(maxScores[2], maxScores[1]);

	for (size_t i = 3; i < N; ++i) {
		//i-3까지의 최댓값 + x o o
		maxScores[i] = maxScores[i - 3] + scores[i - 1];

		//i-2까지의 최댓값 + x o
		maxScores[i] = std::max(maxScores[i], maxScores[i - 2]);

		//뒤의 o를 더해준다
		std::cin >> scores[i];
		maxScores[i] += scores[i];

		//i-1의 최댓값 + x(이번꺼)
		maxScores[i] = std::max(maxScores[i], maxScores[i - 1]);
	}

	std::cout << maxScores.back();

	return 0;
}
