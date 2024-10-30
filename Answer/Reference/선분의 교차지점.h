#pragma once
//참고 문제: 백준 17386, 20149 - 선분 교차

#include <cmath>
//충돌 감지를 했을때만 사용할것, as <= ae/bs <= be
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