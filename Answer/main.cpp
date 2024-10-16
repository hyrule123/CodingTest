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

#include <vector>
#include <cmath>
//shoelace formula.(식이 신발끈 메는것처럼 생김)
//https://mathworld.wolfram.com/PolygonArea.html
struct coord {
	double x, y;
};
double round_precision(double val, double precision) {
	return std::round(val / precision) * precision;
}

std::vector<coord> polygon;
int N;
void solve() {
	std::cin >> N;
	polygon.resize(N);
	
	for (int i = 0; i < N; ++i) {
		std::cin >> polygon[i].x >> polygon[i].y;
	}

	double area = 0;
	for (size_t i = 0; i < polygon.size() - 1; ++i) {
		area += (polygon[i].x * polygon[i + 1].y - polygon[i + 1].x * polygon[i].y);
	}

	//Xn * Y1 - X1 * Yn 
	area += (polygon.back().x * polygon.front().y - polygon.front().x * polygon.back().y);

	//* 1/2
	area *= 0.5;

	//Note that the area of a convex polygon is defined to be positive if the points are arranged in a counterclockwise order and negative if they are in clockwise order (Beyer 1987).
	area = std::abs(area);
	area = round_precision(area, 0.1);

	printf("%.1lf", area);
}