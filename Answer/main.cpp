#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 2470 (두 용액) - 내 풀이 2
*/
int liquids[100000], N, temp[100000];
struct answer {
	int ABS_sum = std::numeric_limits<int>::max(), left, right;
} ans;
int ABS(int i) { if (i < 0) { i = -i; } return i; }

void MergeSort(int start, int end) {
	if (start >= end) { return; }

	int mid = (start + end) / 2;

	MergeSort(start, mid);
	MergeSort(mid + 1, end);

	int l = start;
	int r = mid + 1;
	int cursor = l;

	while (l <= mid && r <= end) {
		if (liquids[l] < liquids[r]) {
			temp[cursor++] = liquids[l++];
		}
		else {
			temp[cursor++] = liquids[r++];
		}
	}

	for (; l <= mid;) {
		temp[cursor++] = liquids[l++];
	}
	for (; r <= end;) {
		temp[cursor++] = liquids[r++];
	}
	
	memcpy(liquids + start, temp + start, sizeof(int) * (end - start + 1));
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> liquids[i];
	}
	MergeSort(0, N - 1);

	int l = 0, r = N - 1;
	while (l < r) {
		int sum = liquids[l] + liquids[r];

		if (ABS(sum) < ans.ABS_sum) {
			ans.ABS_sum = ABS(sum);
			ans.left = liquids[l];
			ans.right = liquids[r];
		}

		if (sum < 0) {
			++l;
		}
		else if (sum > 0) {
			--r;
		}
		
		else {//sum == 0
			break;
		}
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