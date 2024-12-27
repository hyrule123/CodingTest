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
백준 1168 (요세푸스 문제 2) [세그먼트 트리]
*/
#include <cmath>
#include <vector>
constexpr int MAX = 100'000;
vector<int> segtree;
int N, K, seg_size;

void init(int cur_idx, int search_l, int search_r) {
	if (search_l >= search_r) {
		segtree[cur_idx] = 1;
		return;
	}

	int mid = (search_l + search_r) / 2, left = cur_idx * 2, right = left + 1;

	init(left, search_l, mid);
	init(right, mid + 1, search_r);

	segtree[cur_idx] = segtree[left] + segtree[right];
}

int query(int cur_idx, int search_l, int search_r, int target_num) {
	if (search_l >= search_r) {
		segtree[cur_idx] = 0;
		return search_l;
	}

	int mid = (search_l + search_r) / 2, left = cur_idx * 2, right = left + 1;
	int ret = 0;
	if (target_num <= segtree[left]) {
		ret = query(left, search_l, mid, target_num);
	}
	else {
		ret = query(right, mid + 1, search_r, target_num - segtree[left]);
	}

	segtree[cur_idx] = segtree[left] + segtree[right];
	
	return ret;
}

void solve() {
	cin >> N >> K;
	seg_size = (int)pow(2.0, ceil(log2((double)N)) + 1);
	segtree.resize(seg_size);

	init(1, 1, N);

	cout << '<';
	int remain = N, n_th = K;
	while (remain) {
		/*
		7, 3일 경우
		1회 처음에서 3번째 { 1, 2, {3}, 4, 5, 6, 7 }
		2회 처음에서 5번째 { 1, 2, {3}, 4, 5, {6}, 7 }
		3회 처음에서 2번째 { 1, {2}, {3}, 4, 5, {6}, 7 }
		...
		규칙: (K + (K - 1) * N회) % (남은 인원 수)
		*/
		cout << query(1, 1, N, n_th);
		--remain;
		if (remain) {
			n_th = (n_th + K - 1) % remain;
			if (n_th == 0) { n_th = remain; }
			cout << ", ";
		}
	}

	for (int i = 1; i <= N; ++i) {

	}
	cout << '>';
}