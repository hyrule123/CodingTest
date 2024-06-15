#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif

#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////
#include <vector>
using uint64 = std::uint64_t;

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	//최대 10^9 * 10^9 = 10^18 < 2^64
	uint64 N; std::cin >> N;
	std::vector<uint64> cityDistance(N);
	for (uint64 i = 0; i < N - 1; ++i) {
		std::cin >> cityDistance[i];
	}

	uint64 sumPrice = 0;
	uint64 curGasPrice; std::cin >> curGasPrice;
	uint64 accDistance = 0;
	for (uint64 i = 0; i < N; ++i) {
		accDistance += cityDistance[i];

		uint64 nextGasPrice; std::cin >> nextGasPrice;
		//내가 이 도시에서 사야하는 기름값보다 i번째 도시의 기름값이 싸다면 거기까지 갈수있을만큼만 넣는다
		//거기서부터 새로넣어서 가는게 더 싸게먹히니까
		if (nextGasPrice < curGasPrice) {
			sumPrice += accDistance * curGasPrice;
			accDistance = 0;
			curGasPrice = nextGasPrice;
		}
	}

	if (accDistance != 0) {
		sumPrice += accDistance * curGasPrice;
	}

	std::cout << sumPrice;
	return 0;
}
