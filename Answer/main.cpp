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
백준 1007 (벡터 매칭) [브루트포스][조합]
최대 N = 20, 벡터를 매칭한다면 10개 벡터가 만들어짐
각 벡터는 +, -(반대방향)을 가짐 -> 2^10
벡터의 조합: (20 * 19) / 2 ( == 20 C 2 ) * (18 * 17) / 2 (== 18 C 2) * ... * (2 * 1) / 2 
-> 20! / 2^10
또한, 순열이 아니라 조합 이므로(순서에 관계 없음)
중복되는 순열 경우의 수만큼 나눠준다(백터 10개 -> 10!)
20! / (2^10 * 10!)
=> 시간 제한은 2초 이므로 전부 대입하면 풀이 불가능 할듯

<정석 풀이>
점을 두 그룹으로 분할(시작점 그룹, 끝점 그룹)
모든 경우의 수에 대해서 시작점 그룹 - 끝점 그룹의 최소값을 구한다
최대 20개의 점을 두개의 그룹으로 분할 -> 20 C 10 = 20! / 10! * 10!
== 20 * 19 * 18 * ... * 11 / 10!
대략 18만번 안에 구할 수 있다
*/

#include <algorithm>
#include <vector>
#include <cmath>

struct vec2
{
	double x, y;

	vec2 operator +(const vec2& o) const
	{
		return { x + o.x, y + o.y };
	}

	vec2 operator -(const vec2& o) const
	{
		return { x - o.x, y - o.y };
	}

	double len() const
	{
		return sqrt(x * x + y * y);
	}
};

vector<vec2> inputs;
int N;
vector<int> comb;

void solve()
{
	cout << fixed;
	cout.precision(6);

	int TC; cin >> TC;
	while (TC--)
	{
		cin >> N;
		inputs.resize(N);

		for (int i = 0; i < N; ++i)
		{
			cin >> inputs[i].x >> inputs[i].y;
		}

		comb.clear();
		comb.resize(N);
		for (int i = N / 2; i < N; ++i)
		{
			comb[i] = 1;
		}

		double ans = numeric_limits<double>::max();
		do
		{
			//시작점 그룹, 끝점 그룹 2개로 분리
			vec2 groups[2]{};
			for (int i = 0; i < N; ++i)
			{
				auto& group = groups[comb[i]];
				group = group + inputs[i];
			}

			double length = (groups[0] - groups[1]).len();
			ans = min(ans, length);
		} while (next_permutation(comb.begin(), comb.end()));

		cout << ans << '\n';
	}
}