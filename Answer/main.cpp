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
백준 7453 (합이 0인 네 정수) [투 포인터][v4]
v4: 인풋 받을때 캐시 적중률 올리면 효과 있는지 확인(A[4000], B[4000], ... -> ABCD[4000][4])
-> 효과 없다? 이런것도 최적화를 해 주는건가...
*/
#include <vector>
#include <algorithm>
constexpr int MAX = 4000;
enum e { a, b, c, d };
enum ee { ab, cd };
int AB[MAX * MAX], CD[MAX * MAX], ABCD[MAX][4], N;

void solve()
{
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> ABCD[i][a] >> ABCD[i][b] >> ABCD[i][c] >> ABCD[i][d];
	}

	for (int idx = 0, i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			AB[idx] = ABCD[i][a] + ABCD[j][b];
			CD[idx] = ABCD[i][c] + ABCD[j][d];
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