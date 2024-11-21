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
백준 1004 (어린 왕자)
출발점과 도착점이 원 바깥에 있으면 얼마든지 돌아가면 되니까
출발점, 도착점이 몇개의 '다른'원 안에 있는지를 검사하면 될듯(같은 원 안일 경우 안쪽에서 돌아서 갈수 있으므로)
*/

struct vec2 {
	double x, y;

	vec2 operator -(const vec2& o) const {
		return { x - o.x, y - o.y };
	}
	double dist_squared(const vec2& o) const {
		vec2 sub = (*this) - o;
		return sub.x * sub.x + sub.y * sub.y;
	}
};

void solve() {
	int T; cin >> T;

	while (T--) {
		vec2 from, to;
		cin >> from.x >> from.y >> to.x >> to.y;

		int n; cin >> n;
		int count = 0;
		while (n--) {
			vec2 center; cin >> center.x >> center.y;
			double r; cin >> r;
			r = r * r;

			double
				f2c = from.dist_squared(center),
				t2c = to.dist_squared(center);

			//둘다 같은 원 안에 있으면 원을 벗어날 필요가 없으므로 continue
			if (f2c <= r && t2c <= r) {
				continue;
			}

			//다른 원일 경우 -> 둘 중 하나만 원 안에 속해 있을 경우
			if (f2c <= r || t2c <= r) {
				++count;
			}
		}
		cout << count << '\n';
	}
}