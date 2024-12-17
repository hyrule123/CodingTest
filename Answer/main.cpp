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
백준 1517 (버블 소트) [세그먼트 트리]
참고 사이트
https://loosie.tistory.com/328
https://leeju.tistory.com/95

* 
오름차순 버블 소트: 자신보다 작은 값이 나오면 swap
자기 자신의 뒤에 있는 자기 자신보다 작은 수의 개수만큼 swap이 발생한다.
ex) {5, 4, 3}에서 5를 버블소트하면 4, 3과 swap 해야 하므로 2회 발생

* 세그먼트 트리를 사용하는 이유
: 정렬되기 전의 배열에서, 자신의 뒤쪽에 존재하는 작은 값의 개수의 합(구간합)을 찾는 용도
segtree range (5, 10) 배열의 5번 인덱스부터 10번 인덱스에 자신보다 작은 수가 몇 개가 있는지?

* 알고리즘 순서
1. 원 배열을 { 숫자, 인덱스 } 순서로 저장
	ex. { 5, 4, 3, 2, 1 } -> { (5, 0), (4, 1), (3, 2), (2, 3), (1, 4) }

2. 배열을 오름차순 정렬(segment tree를 사용하더라도 어차피 정렬은 해야 함)
	{ (1, 4), (2, 3), (3, 2), (4, 1), (5, 0) }

3. 정렬된 배열 순서대로 query, update
	(1, 4)
	query: 4 + 1 = 5번 인덱스부터 끝(5번)까지 1보다 작은 수는 몇개? -> 답에 더한다
	update: 자신의 인덱스 4를 segment tree에 반영
	segtree(4, 4) -> 4번 인덱스에 나보다 작은 숫자는? 1개
	"오름차순 정렬" 되어 있으므로 다음에 segtree에서 탐색할 숫자는 반드시 1보다 큼

	(2, 3)
	query: 3 + 1 = 4번 인덱스부터 끝(5번)까지 2보다 작은 수는 몇개?
	update: 자신의 인덱스 2를 segment tree에 반영

*** 참고사항 ***
* 병합정렬: O(N^2), N = 500'000 -> 250'000'000'000 -> int 범위 초과
*/
#include <vector>
#include <algorithm>
#include <cmath>
using pii = pair<int, int>;
using ll = long long;
#define VAL first
#define IDX second
vector<pii> arr;
vector<int> segtree;	//원소 최대값: N - 1 (자신의 뒤에 있는 배열 원소 중 작은 원소의 개수)
int N;

//target_val = +1
void update_segtree(int cur_idx, int cur_range_l, int cur_range_r, int target_idx) {
	if (cur_range_l == cur_range_r) {
		segtree[cur_idx] += 1;
		return;
	}

	int mid = (cur_range_l + cur_range_r) / 2, child_l = cur_idx * 2, child_r = child_l + 1;

	if (target_idx <= mid) {
		update_segtree(child_l, cur_range_l, mid, target_idx);
	}
	else {
		update_segtree(child_r, mid + 1, cur_range_r, target_idx);
	}
	
	segtree[cur_idx] = segtree[child_l] + segtree[child_r];
}

int query(int cur_idx, int cur_range_l, int cur_range_r, int query_l, int query_r) {
	if (query_l > cur_range_r || query_r < cur_range_l) {
		return 0;
	}
	if (query_l <= cur_range_l && cur_range_r <= query_r) {
		return segtree[cur_idx];
	}
	
	int mid = (cur_range_l + cur_range_r) / 2, child_l = cur_idx * 2, child_r = child_l + 1;
	return query(child_l, cur_range_l, mid, query_l, query_r)
		+ query(child_r, mid + 1, cur_range_r, query_l, query_r);
}

void solve() {
	cin >> N;
	arr.resize(N + 1);

	//정렬 대상인 배열을 받아놓는다.
	//정렬 전 원본 순서도 기억해놔야 한다.
	for (int i = 1; i <= N; ++i) {
		cin >> arr[i].VAL;
		arr[i].IDX = i;
	}

	//정렬
	sort(arr.begin() + 1, arr.end());

	//세그먼트 트리의 정확한 개수: 이진 트리이므로 2^(log2(N) + 1)
	//segtree는 1부터 시작하므로 + 1
	segtree.resize((1 << (int)(ceil(log2(N) + 1.0))) + 1);
	
	ll answer = 0;
	for (int i = 1; i <= N; ++i) {
		//정렬되기 전 순서 기준 자신보다 작은 값이 오른쪽에 몇 개 있는지를 확인한다.
		answer += (ll)query(1, 1, N, arr[i].IDX + 1, N);

		//현재 인덱스를 segment tree에 업데이트 한다.
		//이 때, 작은 숫자 순으로 업데이트 했으므로 update 하기 전 segment tree에는 자신보다 작은 값만 있음이 보장된다.
		//다음에 올 숫자도 마찬가지로 현재 숫자보다 큼이 보장된다.
		update_segtree(1, 1, N, arr[i].IDX);
	}

	cout << answer;
}
