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
백준 12020 (LU 분해) [수학]
https://velog.io/@jqdjhy/%EA%B0%80%EC%9A%B0%EC%8A%A4-%EC%86%8C%EA%B1%B0%EB%B2%95

* 더 효율적인 풀이(문제 조건의 band matrix 사용)
	https://codio.tistory.com/entry/%EB%B0%B1%EC%A4%80-12020%EB%B2%88-LU-%EB%B6%84%ED%95%B4-C
*/
int n;
double L[1001][1001], U[1001][1001];

void solve()
{
	cin >> n;
	//L은 단위행렬로 초기화, U는 A 행렬 그대로 입력을 받아준다.
	for (int i = 0; i < n; ++i)
	{
		L[i][i] = 1;
		for (int j = 0; j < n; ++j)
		{
			cin >> U[i][j];
		}
	}

	for (int c = 0; c < n; ++c)
	{
		//pivot: L[r][c]와 곱해질 U행렬의 원소
		double pivot = U[c][c];
		if (pivot == 0) 
		{
			cout << "-1";
			return;
		}

		for (int r = c + 1; r < n; ++r)
		{
			//U는 좌하단 삼각형 부분이 0이어야 한다.
			//U[r][c]를 0으로 만들어주는 L의 값을 구한다.
			L[r][c] = U[r][c] / pivot;
			U[r][c] = 0;

			//L[r][c]가 0이 아닌 값이 되므로
			//L[r][c]와 곱해지는 U의 r열도 수정해주어야 한다.
			//늘어난 값 만큼을 빼 준다.
			for (int i = c + 1; i < n; ++i)
			{
				U[r][i] = U[r][i] - L[r][c] * U[c][i];
			}
		}
	}

	cout.precision(3);
	cout << fixed;
	for (int r = 0; r < n; ++r)
	{
		for (int c = 0; c < n; ++c)
		{
			cout << L[r][c] << ' ';
		}
		cout << '\n';
	}
	for (int r = 0; r < n; ++r)
	{
		for (int c = 0; c < n; ++c)
		{
			cout << U[r][c] << ' ';
		}
		cout << '\n';
	}
}