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
백준 22968 (균형) [DP][Parametric Search]
AVL 트리에서 깊이 h 이상을 달성하기 위한 최소한의 노드 개수 = N(h)
N(1) = 1
N(2) = 2
N(3) = 4 (한쪽 깊이 1, 반대쪽 깊이 2 부터)
N(4) = 7 (한쪽 깊이 2, 반대쪽 깊이 3 부터)
-> N(h) = N(h - 2) + N(h - 1) + 1
*/
#include <cmath>
#include <vector>
constexpr int MAX = 1'000'000'000;
vector<int> min_N_to_build_h;
void precompute() {
	min_N_to_build_h.reserve(50);
	min_N_to_build_h = { 0, 1, 2 };
	while (min_N_to_build_h.back() < MAX) {
		auto h_minus_2 = min_N_to_build_h.end() - 2;
		auto h_minus_1 = min_N_to_build_h.end() - 1;
		min_N_to_build_h.push_back((*h_minus_2) + (*h_minus_1) + 1);
	}
}

int find_height(int start, int end, int N) {
	int ret = start;

	while (start <= end) {
		int mid = (start + end) / 2;
		
		//깊이 h를 만들기 위한 최소한의 N개 이므로
		if (min_N_to_build_h[mid] <= N) {
			ret = mid;
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}

	return ret;
}

int T;
void solve() {
	precompute();

	cin >> T;
	while (T--) {
		int input; cin >> input;
		cout << find_height(1, (int)min_N_to_build_h.size() - 1, input) << '\n';
	}
}