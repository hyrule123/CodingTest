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
	auto operator <=> (const vector2& o) const {
		if (x == o.x) {
			return y <=> o.y;
		}
		return x <=> o.x;
	}

	auto operator == (const vector2& o) const {
		return x == o.x && y == o.y;
	}
	auto operator != (const vector2& o) const {
		return !((*this) == o);
	}

	friend std::istream& operator >> (std::istream& i, vector2& v) {
		i >> v.x >> v.y;
		return i;
	}
};

constexpr double epsilon = 10e-9;
using cv = const vector2&;

//충돌 감지를 했을때만 사용할것, as <= ae/bs <= be
bool find_intersection(cv _1, cv _2, cv _3, cv _4, vector2& _out) {
	//x(1 * 2) -> x1 * x2라고 할 때
	//cross12 * 34 - cross34 * 12 공식이라고 외워두자
	//nom 1: _1.cross(_2) * x(3 - 4) - _3.cross(_4) * x(1 - 2)
	//nom 2: _1.cross(_2) * y(3 - 4) - _3.cross(_4) * y(1 - 2)
	//denom: x(1 - 2) * y(3 - 4) - y(1 - 2) * x(3 - 4)
	//교점 (x, y) == (nom1 / denom, nom2 / denom)
	//if(denom == 0): 평행(점 한 곳만 겹침 or 선의 부분이 겹침)

	bool ret{};
	double denom = (_1.x - _2.x) * (_3.y - _4.y) - (_1.y - _2.y) * (_3.x - _4.x);
	if (abs(denom) < epsilon) {
		//한 점만 겹칠 때
		if (_2 <= _3 && _2 == _3) {
			_out = _2;
			ret = true;
		}
		else if (_4 <= _1 && _4 == _1) {
			_out = _4;
			ret = true;
		}
	}
	else {
		double
			nom1 = _1.cross(_2) * (_3.x - _4.x) - _3.cross(_4) * (_1.x - _2.x),
			nom2 = _1.cross(_2) * (_3.y - _4.y) - _3.cross(_4) * (_1.y - _2.y);
		ret = true;
		_out = { nom1 / denom, nom2 / denom };
	}

	return ret;
}

void solve() {
	std::cout.setf(std::ios::fixed);
	std::cout.precision(9);

	vector2 as, ae, bs, be;
	std::cin >> as >> ae >> bs >> be;

	if (ae < as) { std::swap(ae, as); }
	if (be < bs) { std::swap(be, bs); };

	vector2 line_a = ae - as;
	vector2 line_b = be - bs;

	//as->ae 벡터와 as->bs, as->be 벡터를 각각 외적 후 곱
	double ccw1 = line_a.cross(bs - as) * line_a.cross(be - as);

	//bs->be 벡터와 bs->as, bs->ae 벡터를 각각 외적 후 곱
	double ccw2 = line_b.cross(as - bs) * line_b.cross(ae - bs);

	//둘 다 0일 경우: 기울기가 같다
	//선분의 최소값, 최대값을 구분해준 다음
	//a선분의 최대 < b선분의 최소 || a선분의 최소 > b선분의 최대
	if (ccw1 == 0.0 && ccw2 == 0.0) {
		//접촉중이 아닌 경우를 !연산
		std::cout << (int)!(be < as || ae < bs) << '\n';
		vector2 point;
		if (find_intersection(as, ae, bs, be, point)) {
			std::cout << point.x << ' ' << point.y;
		}
	}
	//ccw 1과 2가 둘다 음수여야 교차한다는 뜻.
	else if(ccw1 <= 0.0 && ccw2 <= 0.0) {
		
		bool is_intersect = (ccw1 <= 0.0 && ccw2 <= 0.0);
		std::cout << (int)is_intersect << '\n';
		vector2 point;
		if (find_intersection(as, ae, bs, be, point)) {
			std::cout << point.x << ' ' << point.y;
		}
	}
	else {
		std::cout << 0;
	}
}