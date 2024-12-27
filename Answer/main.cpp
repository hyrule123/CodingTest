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
백준 20149 (선분 교차 3) [복습][기하]

CCW: 선분 AB -> 선분 AC가 양수이면 반시계 방향

*/

constexpr double epsilon = numeric_limits<double>::epsilon();
struct vec3 {
	double x = 0, y = 0, z = 0;
	auto operator <=> (const vec3& other) const {
		if (x == other.x) {
			if (y == other.y) {
				return z <=> other.z;
			}
			return y <=> other.y;
		}
		return x <=> other.x;
	}

	bool operator == (const vec3& o) const {
		return x == o.x && y == o.y && z == o.z;
	}

	vec3 operator -(const vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	//sarrus rule
	//i   j   k
	//x   y   z
	//o.x o.y o.z
	vec3 cross(const vec3& o) const {
		return { (y * o.z - z * o.y), (z * o.x - x * o.z), (x * o.y - y * o.x)};
	}

	//충돌 감지가 확정되었을 경우에만 사용 가능
	static bool find_intersection_2d(const vec3& a, const vec3& b, const vec3& c, const vec3& d, vec3& result) {
		//두 점 p1, p2를 지나는 직선의 방정식 
		//이 때 z 좌표는 공차좌표로 1을 넣어주어야 한다
		//p1 x p2 (cross) -> ax + by + c = 0 방정식의 계수(a, b, c)
		vec3 eq_ab = vec3(a.x, a.y, 1).cross(vec3(b.x, b.y, 1));
		vec3 eq_cd = vec3(c.x, c.y, 1).cross(vec3(d.x, d.y, 1));

		/*
		Cramer's Rule을 통한 연립 방정식 풀이
		https://blog.naver.com/ybjang/222729617938
		|a1 b1| =  |-c1|
		|a2 b2|    |-c2|
		*/
		double det = eq_ab.x * eq_cd.y - eq_cd.x * eq_ab.y;
		//det 0일 경우 기울기가 같다
		if (-epsilon < det && det < epsilon) {
			if (a != d && b == c) {
				result = b;
				return true;
			}
			if (b != c && a == d) {
				result = a;
				return true;
			}

			return false;
		}

		/*
		|-c1 b1|
		|-c2 b2|
		*/
		double nom1 = -eq_ab.z * eq_cd.y - eq_ab.y * -eq_cd.z;
		/*
		|a1 -c1|
		|a2 -c2|
		*/
		double nom2 = eq_ab.x * -eq_cd.z - (-eq_ab.z * eq_cd.x);

		result.x = nom1 / det;
		result.y = nom2 / det;

		return true;
	}
};

void solve() {
	cout << fixed; cout.precision(9);

	vec3 a, b, c, d; 
	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

	if (a > b) { swap(a, b); }
	if (c > d) { swap(c, d); }

	//벡터 ab 를 벡터 ac, ad에 대해 외적하여 어느 방향인지 확인
	//한 쪽 선분의 끝은 시계방향, 다른 한 쪽 선분의 끝은 반시계 방향이여야 한다
	//즉, 둘이 곱한 값이 음수(또는 0)이 나와야 함
	vec3 ab_ac = (b - a).cross(c - a);
	vec3 ab_ad = (b - a).cross(d - a);
	double ab_ccw_result = ab_ac.z * ab_ad.z;

	//벡터 cd를 벡터 ca와 벡터 cb에 대해 외적하여 어느 방향인지 확인
	vec3 cd_ca = (d - c).cross(a - c);
	vec3 cd_cb = (d - c).cross(b - c);
	double cd_ccw_result = cd_ca.z * cd_cb.z;

	//ccw 결과가 0일 경우에는 기울기가 같다는 뜻
	//두 선분의 기울기가 같을 경우 일치하거나, 한 점에서 만나거나, 아예 만나지 않는다.
	if (ab_ccw_result == 0 && cd_ccw_result == 0) {
		//둘이 만나지 않는 경우를 연산
		bool is_intersecting = !(d < a || b < c);
		cout << is_intersecting << '\n';
		if (is_intersecting) {
			vec3 result{};

			if (vec3::find_intersection_2d(a, b, c, d, result)) {
				cout << result.x << ' ' << result.y;
			}
		}
	}
	//하나만 0 이거나 둘 다 음수일 경우: 교차
	else if (ab_ccw_result <= 0 && cd_ccw_result <= 0) {
		vec3 result{};
		bool is_intersecting = vec3::find_intersection_2d(a, b, c, d, result);
		cout << is_intersecting << '\n';
		if (is_intersecting) {
			cout << result.x << ' ' << result.y;
		}
	}
	else {
		cout << false;
	}
}