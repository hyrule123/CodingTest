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
백준 16975 (수열과 쿼리 21) [세그먼트 트리]
* 힌트에서는 lazy propagation을 사용하지 않고도 풀 수 있다고 하였음.
* 검색해 보니 수열에서 하나의 값만 업데이트/쿼리 하는 것을 '점'이라고 부르는 듯 하다.
	update(3, 3) -> 점 업데이트, query(3, 3) -> 점 쿼리
* 펜윅 트리와 세그먼트 트리는 일반적으로 '점 업데이트'와 '구간 쿼리' 를 logN 시간 안에 수행 가능하고,
* 여기에 lazy propagation을 적용시키면 '구간 업데이트'와 '구간 쿼리'를 logN 시간 안에 수행 가능하다.

* '구간 업데이트'와 '점 쿼리'만을 수행하는 경우에는 lazy propagation이 필요하지 않다.

* 내 풀이 전략: 숫자 배열은 그냥 냅두고, 이후 구간 업데이트 값을 세그먼트 트리에 저장
	세그먼트 트리에는 해당 범위에 얼마나 더해야 하는지를 저장
	[0, 3] 범위에 -2 -> 만약 [0, 3] 노드가 있다면 해당 노드에 -2를 저장
	[3, 3] 범위에 -1 -> [3, 3]노드에 -1을 저장
	query[3, 3] -> 모든 노드를 타고 들어가면서 합을 전부 더한다
	[0, 3]: -2 + [3, 3]: -1 -> -3이 출력
	해당 결과를 배열에 저장된 값에 더하면 답
*/
using ll = long long;
int N;
ll inputs[100'001], segtree[100'000 * 4 + 1];

int range_l, range_r, update_val;
void update_segtree(int cur_idx, int search_l, int search_r) {
	if (search_r < range_l || range_r < search_l) {
		return;
	}

	if (range_l <= search_l && search_r <= range_r) {
		segtree[cur_idx] += update_val;
		return;
	}

	int mid = (search_l + search_r) / 2, left = cur_idx * 2, right = left + 1;

	update_segtree(left, search_l, mid);
	update_segtree(right, mid + 1, search_r);

	//구간합이 아니므로 부모 노드에 좌우 노드의 합을 더하지 않는다.
}

//지정한 구간에 수를 얼마나 더해야하는지?
ll query(int cur_idx, int search_l, int search_r) {
	if (search_r < range_l || range_r < search_l) {
		return 0;
	}

	if (range_l <= search_l && search_r <= range_r) {
		return segtree[cur_idx];
	}

	int mid = (search_l + search_r) / 2, left = cur_idx * 2, right = left + 1;

	//이 부분이 중요, 모든 세그먼트 노드의 값을 더한다(구간합이 아님)
	ll ret = segtree[cur_idx];

	ret += query(left, search_l, mid);
	ret += query(right, mid + 1, search_r);
	return ret;
}


void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> inputs[i];
	}

	int M; cin >> M;
	while (M--) {
		int Q; cin >> Q;
		if (Q == 1) {
			cin >> range_l >> range_r >> update_val;
			update_segtree(1, 1, N);
		}
		else {
			cin >> range_l;
			range_r = range_l;
			ll output = inputs[range_l]
				+ query(1, 1, N);
			cout << output << '\n';
		}
	}
}