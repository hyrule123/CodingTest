#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

using uint = unsigned int;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	uint N, K; std::cin >> N >> K;

	//숫자 x == 이분탐색으로 정함
	//숫자 y == 숫자 x보다 작거나 같은 숫자가 몇개인가?
	//만약 y가 K보다 많다면 end를 낮추고, 그렇지 않다면 start를 올린다.
	//2차원 N*N 행렬의 각 행 i에 x보다 작거나 같은 수는 min(x / i, N)
	uint start = 1, end = K;
	uint result = 1;
	while (start <= end) {
		uint x = (start + end) / 2;

		uint y = 0;
		for (uint i = 1; i <= N; ++i) {
			y += std::min(x / i, N);
		}

		//K개보다 모자라면 저점을 올려준다
		if (y < K) {
			start = x + 1;
		}
		//K보다 많을 경우 답일 수도 있으므로(K보다 같거나 많은 가장 첫 번째 인덱스) 
		//result에 할당하고 고점을 내려준다.
		else {
			result = x;
			end = x - 1;
		}
	}
	std::cout << result;

	return 0;
}