#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;
void solve();
int main() 
{
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

/*
백준 9574 (Goldilocks and the N Cows) [투 포인터?]
*/
#include <vector>
#include <algorithm>
int N, prod_cold, prod_cozy, prod_hot;
vector<int> low_limit, high_limit;

void solve() {
	cin >> N >> prod_cold >> prod_cozy >> prod_hot;
	low_limit.resize(N + 1);
	high_limit.resize(N + 1);
	for (int i = 1; i <= N; ++i) {
		cin >> low_limit[i] >> high_limit[i];
	}
	//temp_from, _to[i]보다 높은 값을 가진 소들은 n - i 마리가 존재한다
	sort(low_limit.begin() + 1, low_limit.end());
	sort(high_limit.begin() + 1, high_limit.end());

	int ans = -1;
	for (int l = N, h = N; l >= 1; --l) 
	{
		//현재 온도 low_limit[l]일 때
		//춥다고 느낀 소의 수: N - l
		int cold_cow = N - l;
		
		//덥다고 느낀 소의 수를 high_limit[h] 라고 가정하면
		//기준 온도는 low_limit[l] 이므로 high_limit[h]가 low_limit[l] 미만이 되는 때를 찾아야 한다.
		//그러면 h 이하의 소들(==h마리)은 전부 low_limit[l]을 덥다고 느낄 것이다.
		while (1 <= h && low_limit[l] <= high_limit[h])
		{
			--h;
		}
		int hot_cow = h;

		//cold_cow와 hot_cow를 구했으니 N - cold_cow - hot_cow 하면 기온이 적절한 소가 나온다
		int cozy_cow = N - cold_cow - hot_cow;

		ans = max(ans, prod_cold * cold_cow + prod_cozy * cozy_cow + prod_hot * hot_cow);
	}
	cout << ans;
}