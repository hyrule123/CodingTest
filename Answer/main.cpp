#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>


//LIS 배열 의미: 길이가 idx인 부분 증가수열의 마지막 원소의 값 and 그 중 가장 작은 값
//예를들어 이번에 20을 넣는데
//LIS[3] 이 30, LIS[1]이 10 이라면 LIS[2] = 20을 넣어주면 된다.
std::vector<int> LIS;
void InsertLIS(int _u) {
	if (LIS.back() < _u) {
		LIS.push_back(_u);
		return;
	}

	int start = 0, end = (int)LIS.size() - 1u;
	int idx = 0;
	while (start <= end) {
		int mid = (start + end) / 2;
		
		if (_u <= LIS[mid]) {
			idx = mid;
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}

	LIS[idx] = _u;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	int N; std::cin >> N;
	LIS.reserve(N);
	LIS.push_back(0);
	std::cin >> LIS.back();
	for (int i = 1; i < N; ++i) {
		int input; std::cin >> input;
		InsertLIS(input);
	}
	std::cout << LIS.size();

	return 0;
}