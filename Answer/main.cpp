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
백준 7453 (합이 0인 네 정수) [v3][투 포인터]
*/
#include <vector>
#include <algorithm>
constexpr int MAX = 4000;
int AB[MAX * MAX], CD[MAX * MAX], A[MAX], B[MAX], C[MAX], D[MAX], N;

void solve()
{
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> A[i] >> B[i] >> C[i] >> D[i];
	}

	int idx = 0;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			AB[idx] = A[r] + B[c];
			CD[idx] = C[r] + D[c];
			++idx;
		}
	}

	sort(begin(AB), begin(AB) + N * N);
	sort(begin(CD), begin(CD) + N * N);

	long long ans = 0;
	int l = 0, r = N * N - 1;
	while (l < N * N && r >= 0)
	{
		int sum = AB[l] + CD[r];
		if (sum < 0)
		{
			++l;
		}
		else if (sum > 0)
		{
			--r;
		}
		else
		{
			int l_n = l + 1, r_n = r - 1;

			while (l_n < N * N && AB[l] == AB[l_n])
			{
				++l_n;
			}
			while (r_n >= 0 && CD[r] == CD[r_n])
			{
				--r_n;
			}

			ans += (long long)(l_n - l) * (long long)(r - r_n);

			l = l_n; r = r_n;
		}
	}

	cout << ans;
}