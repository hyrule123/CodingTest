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
백준 9345 (디지털 비디오 디스크(DVDs)) [세그먼트 트리][오답2]
* 첫번째 풀이와 오답 이유
분탕이 DVD의 순서를 바꿨을 때, 그냥 바뀐 DVD들을 1로 마킹해놓고
구간합을 구했을 때 0이 아니면 DVD가 뒤섞였다고 판정하려 했음
하지만 이렇게 했을 시 다음과 같은 경우에 대응이 안 됨
1, 2, 3, 4 -> 3, 4, 1, 2, -> 2, 1, 4, 3 -> sum[0, 1)과 sum[2, 3)은 정답이지만
내가 구상한 아이디어로는 오답이 나오게 됨

* 두번째 풀이와 오답 이유
DVD 순서는 0, 1, 2, 3의 등차 수열이므로 등차수열의 합 공식을 이용해 정확한 값을 빠르게 구할 수 있다
분탕이 뒤집어놓은 DVD 순서는 세그먼트 트리에 계속 갱신해줘야 함
만약 등차수열의 합 != DVD 합 일 경우 DVD 순서에 문제가 있는것
-> 0, 1, 2, 3, 4: query(1, 3) = 6
-> 3, 4, 2, 0, 1 : query(1, 3) = 6
순서가 명백히 바꼈지만 참을 반환한다
*/
int N, segtree[400'000], leaf_num;

void build_segtree(int cur_idx, int start, int end) {
	if (start >= end) {
		segtree[cur_idx] = leaf_num++;
		return;
	}

	int mid = (start + end) / 2, left = cur_idx * 2 + 1, right = left + 1;

	build_segtree(left, start, mid);
	build_segtree(right, mid + 1, end);

	segtree[cur_idx] = segtree[left] + segtree[right];
}

int target_idx, target_val;
void modify_segtree(int cur_idx, int start, int end) {
	if (start >= end) {
		segtree[cur_idx] = target_val;
		return;
	}

	int mid = (start + end) / 2, left = cur_idx * 2 + 1, right = left + 1;
	if (target_idx <= mid) {
		modify_segtree(left, start, mid);
	}
	else {
		modify_segtree(right, mid + 1, end);
	}
	
	segtree[cur_idx] = segtree[left] + segtree[right];
}

int query_l, query_r;
int query_segtree(int cur_idx, int start, int end) {
	if (query_r < start || end < query_l) {
		return 0;
	}
	if (query_l <= start && end <= query_r) {
		return segtree[cur_idx];
	}

	int mid = (start + end) / 2, left = cur_idx * 2 + 1, right = left + 1;

	return
		query_segtree(left, start, mid)
		+ query_segtree(right, mid + 1, end);
}

void solve() {
	int T; cin >> T;
	while (T--) {
		int K;
		cin >> N >> K;
		
		memset(segtree, 0, sizeof(segtree));
		leaf_num = 0;
		build_segtree(0, 0, N - 1);

		while (K--) {
			int Q, A, B; cin >> Q >> A >> B;
			if (0 == Q) {
				//현재 A, B에 들어있는 DVD 번호를 가져온다.
				query_l = A, query_r = A;
				int dvd_in_A = query_segtree(0, 0, N - 1);

				query_l = B, query_r = B;
				int dvd_in_B = query_segtree(0, 0, N - 1);
				
				//A와 B에 들어있던 DVD를 맞바꾼다
				target_idx = A, target_val = dvd_in_B;
				modify_segtree(0, 0, N - 1);

				target_idx = B, target_val = dvd_in_A;
				modify_segtree(0, 0, N - 1);
			}
			else {
				query_l = A, query_r = B;
				int result = query_segtree(0, 0, N - 1);
				int original = (A + B) * (B - A + 1) / 2;

				cout << (result == original ? "YES\n" : "NO\n");
			}
		}
	}
}