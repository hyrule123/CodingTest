#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;

	solve();
	return 0;
}
/*
백준 2170 (선 긋기) [스위핑]
*/
using pii = pair<int, int>;
#define FROM first
#define TO second
int N;
pii arr[1'000'000], temp[1'000'000];

void mergesort(int start, int end) {
	if (start >= end) { return; }

	int mid = (start + end) / 2;
	mergesort(start, mid);
	mergesort(mid + 1, end);

	int l = start, r = mid + 1, cursor = 0;
	while (l <= mid && r <= end) {
		if (arr[l] <= arr[r]) {
			temp[cursor++] = arr[l++];
		}
		else {
			temp[cursor++] = arr[r++];
		}
	}

	while (l <= mid) {
		temp[cursor++] = arr[l++];
	}
	while (r <= end) {
		temp[cursor++] = arr[r++];
	}

	memcpy(arr + start, temp, sizeof(pii) * (end - start + 1));
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i].FROM >> arr[i].TO;
	}

	mergesort(0, N - 1);

	//경우의 수: 3가지
	//1. 바로 전에 그린 선과 현재 그린 선이 일치
	//2. 부분 일치
	//3. 미일치

	//계산 완료된 시작점과 끝점
	int from = arr[0].FROM, to = arr[0].TO;
	int sum = to - from;
	for (int i = 1; i < N; ++i) {
		//정렬했으므로 arr[i - 1].FROM <= arr[i].FROM은 언제나 참

		//선이 미일치하는 경우
		if (to <= arr[i].FROM) {
			sum = sum + (arr[i].TO - arr[i].FROM);
			from = arr[i].FROM;
			to = arr[i].TO;
		}

		else if (arr[i].FROM <= to) {
			//부분 일치 할 경우
			if (to <= arr[i].TO) {
				sum = sum + (arr[i].TO - to);
				from = to;
				to = arr[i].TO;
			}
			//이미 합산된 선일 경우 아무것도 하지 않는다
		}
	}

	cout << sum;
}