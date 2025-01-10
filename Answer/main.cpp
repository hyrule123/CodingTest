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
백준 2836 (수상 택시) [스위핑]
* 목적지 0, 도착지 M이므로 이동거리는 M
* 정방향으로 이동하는 경우 그냥 태웠다가 내려주면 되므로 집으로 이동하는 거리에 포함된다.
* 대신 역방향으로 이동하는 경우에는 뒤로 갔다가 다시 앞으로 가야한다.
* M(정방향 이동 거리) + (역방향 거리 * 2)
	M: 최대 10억, 역방향 최대 10억 -> int로 감당 안됨
* 역방향 스위핑을 하면 될듯?
* 
*/
#include <array>
#include <algorithm>
using uint = unsigned int;
using puu = pair<uint, uint>;
int N, M, reverse_count;
array<puu, 300'000> inputs;
#define FROM first
#define TO second

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		auto& cur_input = inputs[reverse_count];
		cin >> cur_input.FROM >> cur_input.TO;
		if (cur_input.FROM <= cur_input.TO) {
			continue;
		}
		++reverse_count;
	}

	sort(inputs.begin(), inputs.begin() + reverse_count, greater_equal<puu>());

	uint total = 0,
		r_computed_from = numeric_limits<uint>::min(),
		r_computed_to = numeric_limits<uint>::max();
	for (uint i = 0; i < reverse_count; ++i) {
		auto& input = inputs[i];
		//겹치지 않음
		if (input.FROM <= r_computed_to) {
			total += (input.FROM - input.TO);
			r_computed_from = input.FROM;
			r_computed_to = input.TO;
		}
		else if (input.TO <= r_computed_to) {
			total += (r_computed_to - input.TO);
			r_computed_to = input.TO;
		}
		//이미 게산된 범위 안에 있을 경우 skip
	}

	uint ans = M + total * 2;
	cout << ans;
}