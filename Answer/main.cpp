#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1806 (부분합)
*/
int N, ser[100000], S;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> S;
	for (int i = 0; i < N; ++i) {
		std::cin >> ser[i];
	}

	int l = 0;
	int r = 0;
	int sum = ser[0];
	int minLen = std::numeric_limits<int>::max();
	while (true) {
		//S에 도달하지 못했는데 더이상 진행 불가능할 경우 break
		if (sum < S) {
			if (r < N) {
				sum += ser[++r];
			}
			else {
				break;
			}
		}
		//S를 넘어섰다면 부분합 시작점을 오른쪽으로(sum이 S(양수)보다 크므로 무조건 양수이고, 이는 곧 l < r)
		else {
			minLen = std::min(minLen, r - l + 1);
			sum -= ser[l]; ++l;
		}
	}
	
	if (minLen == std::numeric_limits<int>::max()) {
		std::cout << 0;
	}
	else {
		std::cout << minLen;
	}

	return 0;
}