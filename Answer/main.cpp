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
백준 2042 (구간 합 구하기) [세그먼트 트리]
*/
using ll = int64_t;
constexpr ll MAX = 1'000'000;
ll N, M, K, segtree[MAX * 4 + 1];

/*
빌드: 재귀 형태로 탐색
*/
ll build_segtree(ll cur, ll start, ll end) {
	if (start >= end) {
		//전위 순회 이므로 리프노드에서 값을 받아올 경우 1, 2, 3, ... 순서로 받아옴
		cin >> segtree[cur]; 
		return segtree[cur];
	}

	ll mid = (start + end) / 2;
	ll left = cur * 2, right = left + 1;

	segtree[cur] = 
		build_segtree(left, start, mid) + 
		build_segtree(right, mid + 1, end);

	return segtree[cur];
}

//변경: 범위 안의 구간만 탐색(이분 탐색)
ll modify(ll cur, ll start, ll end, ll target_idx, ll modify_to) {
	if (start >= end) { 
		segtree[cur] = modify_to; return modify_to; 
	}

	ll mid = (start + end) / 2;
	ll left = cur * 2, right = left + 1;

	//분할 탐색
	if (target_idx <= mid) {
		segtree[cur] = modify(left, start, mid, target_idx, modify_to) + segtree[right];
	}
	else {
		segtree[cur] = segtree[left] + modify(right, mid + 1, end, target_idx, modify_to);
	}

	return segtree[cur];
}

/* 구간합 쿼리
탐색 범위에서 완전히 벗어나는 경우: 0 반환
현재 탐색 범위(start~end)안일 경우: 구간합(segtree[cur])을 반환
부분적으로만 겹칠 경우: 재귀탐색 수행
*/
ll query(ll cur, ll start, ll end, ll from, ll to) {
	//찾고자 하는 범위 바깥인 경우
	if (end < from || to < start) {
		return 0;
	}

	//현재 탐색범위가 구간합 범위 안일 경우
	if (from <= start && end <= to) {
		return segtree[cur];
	}

	//일부만 겹치는 경우: 좌우 분할 탐색
	ll mid = (start + end) / 2;
	ll left = cur * 2, right = left + 1;
	
	return query(left, start, mid, from, to)
		+ query(right, mid + 1, end, from, to);
}

void solve() {
	cin >> N >> M >> K;
	build_segtree(1, 1, N);

	for (int i = 0; i < M + K; ++i) {
		ll a, b, c; cin >> a >> b >> c;
		switch (a) {
		case 1ll: {
			modify(1, 1, N, b, c);
			break;
		}
		case 2ll: {
			cout << query(1, 1, N, b, c) << '\n';
			break;
		}
		}
	}
}
