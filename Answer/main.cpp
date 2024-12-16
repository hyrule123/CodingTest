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
백준 11505 (구간 곱 구하기) [세그먼트 트리]
*/
using ull = unsigned long long;
constexpr ull mod = 1'000'000'007, MAX = 1'000'000;

ull segtree[MAX * 4 + 1], N, M, K;
ull build_segtree(ull cur, ull start, ull end) {
	if (start >= end) {
		cin >> segtree[cur];
		return segtree[cur] %= mod;
	}
	
	ull mid = (start + end) / 2, left = cur * 2, right = left + 1;

	segtree[cur] =
		(build_segtree(left, start, mid)
			* build_segtree(right, mid + 1, end)) % mod;

	return segtree[cur];
}

ull modify_segtree(ull cur, ull start, ull end, ull target_idx, ull target_val) {
	if (start >= end && start == target_idx) {
		segtree[cur] = target_val;
		segtree[cur] %= mod;
		return segtree[cur];
	}

	ull mid = (start + end) / 2, left = cur * 2, right = left + 1;

	if (target_idx <= mid) {
		segtree[cur] =
			(modify_segtree(left, start, mid, target_idx, target_val)
				* segtree[right]) % mod;
	}
	else {
		segtree[cur] =
			(segtree[left]
				* modify_segtree(right, mid + 1, end, target_idx, target_val)) % mod;
	}

	return segtree[cur];
}

ull partmul_segtree(ull cur, ull start, ull end, ull range_start, ull range_end) {
	//둘이 겹치는 범위가 없을 경우
	if (start > range_end || end < range_start) { 
		return 1;
	}
	//현재 탐색범위가 구간합 범위 안에 완벽히 들어올 경우
	if (range_start <= start && end <= range_end) {
		return segtree[cur];
	}

	ull mid = (start + end) / 2, left = cur * 2, right = left + 1;

	//일부만 겹칠 경우
	return (partmul_segtree(left, start, mid, range_start, range_end)
		* partmul_segtree(right, mid + 1, end, range_start, range_end)) % mod;
}

void solve() {
	cin >> N >> M >> K;

	build_segtree(1, 1, N);

	for (ull i = 0; i < M + K; ++i) {
		ull a, b, c; cin >> a >> b >> c;
		if (a == 1) {
			modify_segtree(1, 1, N, b, c);
		}
		else if (a == 2) {
			cout << partmul_segtree(1, 1, N, b, c) << '\n';
		}
	}
}