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

//1  1  1
//x1 y1 z1
//x2 y2 z2
struct coord { 
	double x, y, z; 
	coord cross(const coord& other) {
		return { y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - other.x * y };
	}

	friend std::istream& operator>>(std::istream& str, coord& c) {
		str >> c.x >> c.y;
		c.z = 0;
		return str;
	}
	void operator -= (const coord& c) {
		x -= c.x; y -= c.y;
	}
};


void solve() {
	coord vec1{}, vec2{}, temp{};
	
	std::cin >> vec1 >> vec2 >> temp;
	vec1 -= vec2;
	vec2 -= temp;

	//외적의 Z값 
	// 양수 = 반시계방향
	// 음수 = 시계방향
	// 0 = 일직선
	coord cross = vec1.cross(vec2);

	constexpr double epsilon = std::numeric_limits<double>::epsilon();

	if (std::abs(cross.z) < epsilon) {
		std::cout << 0;
	}
	else if (0 <= cross.z) {
		std::cout << 1;
	}
	else {
		std::cout << -1;
	}
}