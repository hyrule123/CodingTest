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

//백준 1002 (터렛)[epsilon 사용]
//epsilon을 사용하거나
//sqrt를 하지 않고 제곱된 상태를 그대로 사용하거나
//double을 사용하거나 해서 오차를 줄여야 한다
#include <cmath>
constexpr double epsilon = 2.2204460492503131e-016;
struct vec2 {
	double x, y;

	bool operator ==(const vec2& other) const {
		return x == other.x && y == other.y;
	}

	vec2 operator -(const vec2& other) const {
		return { x - other.x, y - other.y };
	}

	double length(const vec2& other) const {
		vec2 v = (*this) - other;
		return sqrt(v.x * v.x + v.y * v.y);
	}
};

void solve() {
	int T; cin >> T;
	while (T--) {
		double ra, rb;
		vec2 a, b; cin >> a.x >> a.y >> ra >> b.x >> b.y >> rb;

		//반지름이 큰 원을 b로 보낸다
		if (rb < ra) {
			swap(a, b);
			swap(ra, rb);
		}

		//동일한 원일 경우 무한대
		if (a == b && ra == rb) {
			cout << -1 << '\n';
			continue;
		}

		double dist = a.length(b);

		//한 원의 중심이 다른 원 안에 속할때
		if (dist < rb) {
			//한 원이 아예 다른 원 안에 속할때: 말이안됨(0개)
			if (dist + ra < rb) {
				cout << 0 << '\n';
			}
			//원의 길이가 동일할 때
			else if (abs(rb - (ra + dist)) < epsilon) {
				cout << 1 << '\n';
			}
			else {
				cout << 2 << '\n';
			}
		}
		else {
			//서로 떨어져 있을 경우
			if (ra + rb < dist) {
				cout << 0 << '\n';
			}
			//붙어 있을경우
			else if (abs(ra + rb - dist) < epsilon) {
				cout << 1 << '\n';
			}
			//둘다 아닐경우
			else {
				cout << 2 << '\n';
			}
		}
	}
}