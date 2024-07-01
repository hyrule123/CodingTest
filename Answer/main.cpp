#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using uint = unsigned int;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	uint K, N; std::cin >> K >> N;
	std::vector<uint> wires(K);
	uint end = 0;
	for (uint i = 0; i < K; ++i) {
		std::cin >> wires[i];
		if (end < wires[i]) {
			end = wires[i];
		}
	}
	
	//Paremetric Search
	//end: 끝 범위를 1만큼 늘려놔야 end 범위까지 찾을 수 있기 때문
	//ex)10 9 8 랜선에서 1개 만드는 경우 답은 10
	//(start, end) = (1, 10) -> (5, 10) -> (7, 10), (8, 10), (9, 10) : 1, 10 범위로 할 경우 답이 9가 나옴
	//(start, end) = (1, 11) -> (6, 11) -> (8, 11), (9, 11), (10, 11) : 답 10
	uint start = 1; ++end;
	uint mid{};
	while (start + 1 < end) {
		mid = (start + end) / 2;

		uint count = 0;
		for (uint i = 0; i < K; ++i) {
			count += wires[i] / mid;
		}
		
		//N개보다 크거나 같을 경우 범위의 오른쪽을 탐색
		//count == N인 값 중에서 가장 큰 값을 찾아야 하므로 '<='
		if (N <= count) {
			start = mid;
		}
		else {
			end = mid;
		}
	}

	std::cout << start;

	return 0;
}