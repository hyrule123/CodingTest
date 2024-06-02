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
std::vector<uint> seq;
std::vector<uint> dp(1);

//https://buyandpray.tistory.com/73
//삽입 규칙: dp[i] = 길이가 'i'인 모든 부분수열의 끝 점 중 '최소값'

//ex) seq = { 10, 20, 30, 15, 20, 30 }
// dp[2]: 길이가 2인 모든 부분수열의 끝 점 중 최소값
// seq[1] = 10 -> dp[1] = 10
// seq[2] = 20 -> 여태까지 생긴 길이 2인 부분수열: { 10, 20 } -> dp[2] = 20
// seq[3] = 30 -> seq[2]와 같은 로직을 통해 dp[3] = 30

// seq[4] = 15 -> { 10, 20 }, { 10, 15 } 
// -> dp[1]에는 길이 1짜리 수열의 최소값인 10, dp[2]에는 이전 최소값인 20이 기록되어 있음
// --> dp[1] 보다 크고, dp[2]보다 작거나 같아야 길이 2인 수열이 되는데, 이젠 15가 새로 생겼으므로 최소값을 갱신

// seq[5] = 20 -> dp[2] = 15, dp[3] = 30 -> seq[5]는 길이 3짜리 수열이 만들어짐을 알수 있다.
// -> dp[3]을 20으로 갱신

void InsertDP(uint _u) {
	//맨 끝값보다 클경우 insert
	if (dp.back() < _u) {
		dp.push_back(_u);
	}
	//작을 경우 이진탐색
	else if (_u < dp.back()) {
		size_t start = 0;
		size_t end = dp.size() - 1;
		size_t mid = end / 2;

		while (start < end) {
			if (dp[mid] < _u && _u <= dp[mid + 1]) {
				dp[mid + 1] = _u;
				break;
			}

			if (dp[mid] < _u) {
				start = mid + 1;
				mid = start + (end - start) / 2;
			}
			else{
				end = mid;
				mid = start + (end - start) / 2;
			}
		}

	}
}

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	size_t N{}; std::cin >> N;
	seq.resize(N + 1);
	dp.reserve(N + 1);

	for (size_t i = 1; i <= N; ++i) {
		std::cin >> seq[i];
		InsertDP(seq[i]);
	}

	std::cout << dp.size() - 1;

	return 0;
}
