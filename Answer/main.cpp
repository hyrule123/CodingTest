#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 2470 (두 용액) - 내 풀이 1(오답)
*/
int liquids[100000], N;
#include <vector>
struct answer {
	int ABS_sum = std::numeric_limits<int>::max(), left, right;
} ans;
int ABS(int i) { if (i < 0) { i = -i; } return i; }

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> liquids[i];
	}

	int left = 0, right = N - 1;

	while (true) {
		//동일 인덱스일경우 움직일 수 있는 포인터를 한칸만 이동시킨다
		//둘다 이동할 수 없을 경우 끝
		if (left == right) {
			if (left + 1 < N) { ++left; }
			if (right - 1 >= 0) { --right; }
			else { break; }
		}

		int sum = liquids[left] + liquids[right];

		//0에 더 가까운 값일 경우 갱신한다.
		if (ABS(sum) < ans.ABS_sum) {
			ans.ABS_sum = ABS(sum);
			ans.left = liquids[left];
			ans.right = liquids[right];
		}

		//0에 가깝게 해야함
		//sum이 0보다 작을 경우: 좀 더 큰 값이 나올수 있도록 작은 값의 포인터를 이동
		if (sum < 0) {
			if (liquids[left] < liquids[right] && left + 1 < N) { ++left; }
			else if (right - 1 >= 0) { --right; }
			else { break; }
		}
		//좀 더 작은 값이 나올 수 있도록 큰 값의 포인터를 이동
		else if (sum > 0) {
			if (liquids[left] > liquids[right] && left + 1 < N) { ++left; }
			else if (right - 1 >= 0) { --right; }
			else { break; }
		}

		//sum = 0이 나오면 가장 가까운값을 찾은 것이므로 중단하고 바로 출력
		else { break; }
	}

	//오름차순 출력
	if (ans.left < ans.right) {
		std::cout << ans.left << ' ' << ans.right;
	}
	else {
		std::cout << ans.right << ' ' << ans.left;
	}

	return 0;
}