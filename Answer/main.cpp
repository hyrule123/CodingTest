#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1450 (냅색문제)
*/
#include <vector>
using ll = long long;
ll N, C, input[30];

std::vector<ll> v1, v2;
//start~end 사이의 짐으로 만들 수 있는 무게의 모든 부분집합을 만든다.
void Insert(std::vector<ll>& v, ll start, ll end, ll sum) {
	//v[start]값을 넣을때, 안넣을때 경우의 수별로 넣어준다.
	if (start < end) {
		Insert(v, start + 1, end, sum);
		Insert(v, start + 1, end, sum + input[start]);
	}
	//start가 끝에 도달했을 경우 sum을 vector에 삽입
	else {
		v.push_back(sum);
	}
}
void MergeSort(std::vector<ll>& temp, ll start, ll end) {
	if (start >= end) { return; }

	ll mid = (start + end) / 2;
	MergeSort(temp, start, mid);
	MergeSort(temp, mid + 1, end);

	ll l = start, r = mid + 1;
	ll cursor = 0;
	while (l <= mid && r <= end) {
		if (v2[l] < v2[r]) {
			temp[cursor++] = v2[l++];
		}
		else {
			temp[cursor++] = v2[r++];
		}
	}
	for (; l <= mid;) {
		temp[cursor++] = v2[l++];
	}
	for (; r <= end;) {
		temp[cursor++] = v2[r++];
	}

	memcpy(v2.data() + start, temp.data(), sizeof(ll) * (end - start + 1));
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	std::cin >> N >> C;
	for (ll i = 0; i < N; ++i) {
		std::cin >> input[i];
	}

	//반반 나눠서 만들수 있는 모든 무게조합을 만든다
	ll half = N / 2;
	Insert(v1, 0, half, 0);
	Insert(v2, half, N, 0);
	
	//v2는 정렬한다
	std::vector<ll> temp(v2.size());
	MergeSort(temp, 0, v2.size() - 1);

	//v1 + v2 해서 C보다 적으면 (==) v2[a] = C - v1[b] 가방에 담을 수 있는 경우의 수가 된다
	ll ans = 0;
	for (ll i = 0; i < (ll)v1.size(); ++i) {
		ll remain_capacity = C - v1[i];
		if (remain_capacity < 0) { continue; }

		//오랜만에 쓰는 이분탐색 parametric search
		ll start = 0, end = (ll)v2.size() - 1, finalIdx = 0;
		while (start <= end) {
			ll mid = (start + end) / 2;

			//마지막 mid 위치를 기록한다
			if (v2[mid] <= remain_capacity) {
				start = mid + 1;
				
				finalIdx = mid;
			}
			else {
				end = mid - 1;
			}
		}

		//냅색에 담을수 있는 짐의 조합들을 모두 추가
		ans += finalIdx + 1;
	}
	std::cout << ans;

	return 0;
}