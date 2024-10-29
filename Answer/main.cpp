#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

struct vector2 {
	double x, y;
	double cross(const vector2& o) const {
		return x * o.y - o.x * y;
	}
	vector2 operator - (const vector2& o) const {
		return { x - o.x, y - o.y };
	}
	bool operator < (const vector2& o) const {
		return x < o.x && y < o.y;
	}

	friend std::istream& operator >> (std::istream& i, vector2& v) {
		i >> v.x >> v.y;
		return i;
	}
};

void solve() {
	vector2 as, ae, bs, be;
	std::cin >> as >> ae >> bs >> be;

	vector2 line_a = ae - as;
	vector2 line_b = be - bs;

	//as->ae 벡터와 as->bs, as->be 벡터를 각각 외적 후 곱
	double ccw1 = line_a.cross(bs - as) * line_a.cross(be - as);

	//bs->be 벡터와 bs->as, bs->ae 벡터를 각각 외적 후 곱
	double ccw2 = line_b.cross(as - bs) * line_b.cross(ae - bs);

	//둘 다 0일 경우: 선분 겹침-> 아예 동떨어져 있거나 접촉
	//선분의 최소값, 최대값을 구분해준 다음
	//최소값 < 최대값인지 확인
	if (ccw1 == 0.0 && ccw2 == 0.0) {
		//bs를 최댓값이라 간주
		if (bs < as) { std::swap(as, bs); }
		if (be < ae) { std::swap(ae, be); }

		//접촉중이 아닌 경우를 !연산
		std::cout << !(ae < bs || be < as);
		return;
	}

	//ccw 1과 2가 둘다 음수여야 교차한다는 뜻.
	std::cout << (int)(ccw1 <= 0.0 && ccw2 <= 0.0);
}