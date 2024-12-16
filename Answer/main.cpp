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
백준 2357 (최솟값과 최댓값) [세그먼트 트리]
*/

constexpr int IDX_MAX = 100'000, VAL_MIN = 1, VAL_MAX = 1'000'000'000;
int N, M;
pair<int, int> segtree[IDX_MAX * 4 + 1];
#ifdef MIN 
#undef MIN
#endif
#ifdef MAX
#undef MAX
#endif
#define MIN first
#define MAX second

const pair<int, int>& build_segtree(int cur_idx, int start, int end) {
	if (start >= end) {
		cin >> segtree[cur_idx].MIN;
		segtree[cur_idx].MAX = segtree[cur_idx].MIN;
		return segtree[cur_idx];
	}

	int mid = (start + end) / 2, left = cur_idx * 2, right = left + 1;

	const auto
		& val_l = build_segtree(left, start, mid),
		& val_r = build_segtree(right, mid + 1, end);

	segtree[cur_idx].MIN = min(val_l.MIN, val_r.MIN);
	segtree[cur_idx].MAX = max(val_l.MAX, val_r.MAX);

	return segtree[cur_idx];
}

pair<int, int> part_min_max(int cur_idx, int start, int end, int from, int to) {
	pair<int, int> ret;
	if (end < from || to < start) {
		ret.MIN = VAL_MAX;
		ret.MAX = VAL_MIN;
		return pair<int, int>{VAL_MAX, VAL_MIN};
	}
	if (from <= start && end <= to) {
		return segtree[cur_idx];
	}

	int mid = (start + end) / 2, left = cur_idx * 2, right = left + 1;

	auto part_l = part_min_max(left, start, mid, from, to),
		part_r = part_min_max(right, mid + 1, end, from, to);

	ret.MIN = min(part_l.MIN, part_r.MIN);
	ret.MAX = max(part_l.MAX, part_r.MAX);

	return ret;
}

void solve() {
	cin >> N >> M;
	build_segtree(1, 1, N);

	while (M--) {
		int a, b; cin >> a >> b;
		auto result = part_min_max(1, 1, N, a, b);
		cout << result.MIN << ' ' << result.MAX << '\n';
	}
}