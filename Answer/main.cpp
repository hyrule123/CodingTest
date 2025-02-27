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
백준 9205(맥주 마시면서 걸어가기) [BFS][다익스트라]
 A
B C
   D
BFS로도 가능하다.
*/
#include <queue>
#include <cmath>
constexpr int INF = 0xfffff; //최대 거리: 65535 + 65535 -> 10만 이상 필요
struct coord
{
	int x, y;
	int dist(const coord& o) const
	{
		return abs(x - o.x) + abs(y - o.y);
	}
};

//0, 
bool djik(const vector<coord>& map)
{
	const int final_dest = (int)map.size() - 1;
	vector<int> dists; dists.resize(map.size(), INF);
	dists[0] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, 0 });
	while (false == pq.empty())
	{
		auto [cur, acc_dist] = pq.top(); pq.pop();
		if (acc_dist > dists[cur]) { continue; }

		for (int i = 0; i < (int)map.size(); ++i)
		{
			if (i == cur) { continue; }

			int next_dist = map[cur].dist(map[i]);
			if (next_dist > 1000) { continue; }
			if (acc_dist + next_dist > dists[i]) { continue; }


			if (i == final_dest) { return true; }
			dists[i] = acc_dist + next_dist;
			pq.push({ i,dists[i] });
		}
	}

	return false;
}

void solve()
{
	int T; cin >> T;
	while (T--)
	{
		int n; cin >> n;
		vector<coord> map;
		map.resize(n + 2);
		for (auto& m : map)
		{
			cin >> m.x >> m.y;
		}
		cout << (djik(map) ? "happy" : "sad") << '\n';
	}
}