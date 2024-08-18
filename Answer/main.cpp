#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 14002 (가장 긴 증가하는 부분 수열 5) : 복습
*/
/*
* 배열의 길이가 100만개 이므로 O(N^2) 방식으로는 해결이 불가능.
* O(N * logN) 알고리즘을 활용해야 해결 가능하다.
* dp[i]의 의미: 길이 i짜리 '가장 긴 증가하는 부분수열(LIS)'의 맨 끝 값 중 가장 작은 값
* ex) 1, 2, 3, 5, 4 -> dp[4]에는 1234와 1235 중 마지막이 작은 수이므로 4가 들어가면 됨
*/
#include <stack>

constexpr int cap = (int)1e6 + 1;
int N, dp[cap], dp_end = 1;

//maxLen: input 값으로 길이 몇 짜리 LIS를 만들었는지를 기록
struct input_trace { int input, lis_len; };
input_trace input_traces[cap];

//return value: val로 만들 수 있는 LIS의 길이
int insert_dp(int val) {
	int ret = -1;

	//같을 경우 스킵
	if (dp[dp_end] == val) {}

	//dp의 마지막 값보다 클 시에는 새로 추가
	else if (dp[dp_end - 1] < val) {
		dp[dp_end] = val;
		ret = dp_end;
		++dp_end;
	}

	//dp의 마지막 값보다 작을 시에는 parametric search를 통해 들어갈 자리를 찾는다.
	else {
		//parametric search
		int start = 0, end = dp_end, foundIdx{};
		while (start <= end) {
			int mid = (start + end) / 2;
			if (val <= dp[mid]) {
				end = mid - 1;
				foundIdx = mid;
			}
			else {
				start = mid + 1;
			}
		}

		dp[foundIdx] = val;
		ret = foundIdx;
	}
	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N;
	dp[0] = std::numeric_limits<int>::min();
	input_traces[0].input = dp[0];
	int longest_LIS = 1;
	for (int i = 1; i <= N; ++i) {
		std::cin >> input_traces[i].input;
		dp[dp_end] = std::numeric_limits<int>::min();

		//input 값으로 만들 수 있는 LIS의 길이를 추가로 기록한다.
		input_traces[i].lis_len = insert_dp(input_traces[i].input);

		if (longest_LIS < input_traces[i].lis_len) {
			longest_LIS = input_traces[i].lis_len;
		}
	}

	//역주적(back trace)
	int cur_len = longest_LIS;
	//LIS의 길이를 구했으므로 더이상 dp 배열은 필요가 없다 -> 재사용한다.

	//역순으로 돌아주면서
	for (int i = N; i >= 1; --i) {

		//가장 긴 LIS 길이를 만들 수 있는 값부터 하나씩 정답으로 기록한다.
		if (cur_len == input_traces[i].lis_len) {
			dp[cur_len] = input_traces[i].input;
			--cur_len;

			if (cur_len == 0) { break; }
		}
	}
	//답을 출력
	std::cout << longest_LIS << '\n';
	for (int i = 1; i <= longest_LIS; ++i) {
		std::cout << dp[i] << ' ';
	}

	return 0;
}