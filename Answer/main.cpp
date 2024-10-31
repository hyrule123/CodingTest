#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

using namespace std;
int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

//필요한 지식
//1. 코사인 법칙으로 각도 구하기
//2. 이등변삼각형의 넓이 구하기
//2-1. 삼각형의 합차 공식
#include <cmath>
constexpr double pi = 3.14159265358979, _2pi = pi * 2;

//코사인 법칙 활용
//c^2 = a^2 + b^2 - 2ab * cos(theta)
//cos(theta) = (a^2 + b^2 - c^2) / 2ab
double get_theta(double opposite_edge, double a, double b) {
	return acos((a * a + b * b - opposite_edge * opposite_edge) / (2 * a * b));
}

void solve() {
	double x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
	
	//원과 원 사이의 거리
	double dist_x = x2 - x1, dist_y = y2 - y1;
	double d = sqrt(dist_x * dist_x + dist_y * dist_y);
	
	//접점이 한곳이거나 겹치지 않는 경우 스킵
	double output = 0;
	if (r1 + r2 <= d) {
		output = 0.0;
	}
	//한 원이 다른 원 안에 포함되는 경우
	else if(d <= abs(r1 - r2)){
		double small = min(r1, r2);
		output = pi * small * small;
	}
	//일부만 겹치는 경우
	else {
		//1. 위 아래 삼각형으로 좌측 theta, 우측 theta 구한다.
		double
			theta_1 = 2 * get_theta(r2, r1, d),
			theta_2 = 2 * get_theta(r1, r2, d);

		//2. 좌우 부채꼴의 넓이를 구한다
		double
			sector_1 = pi * r1 * r1 * (theta_1 / _2pi),
			sector_2 = pi * r2 * r2 * (theta_2 / _2pi);

		//3. 좌우 삼각형의 넓이를 구한다.
		//유도과정
		//3-1. 좌우 삼각형은 각각 두 변이 반지름인 이등변삼각형
		//3-2. 반으로 잘라서 직각삼각형을 만들면 삼각함수를 통해 높이 h와 빗변 o/2를 구할수 있다
		//3-3. h * o / 2 == 삼각형의 넓이 == a * cos(theta/2) * 2a * sin(theta/2) / 2
		//3-4. 삼각함수의 합차공식을 사용하여 정리하면 
		//a^2 * sin(theta) / 2
		double
			isosceles_1 = r1 * r1 * sin(theta_1) / 2.0,
			isosceles_2 = r2 * r2 * sin(theta_2) / 2.0;

		//4. 부채꼴 1 + 부채꼴 2 - 삼각형 1 - 삼각형 2 = 겹치는 부분
		double ans = sector_1 + sector_2 - isosceles_1 - isosceles_2;
		ans *= 1000.0;
		output = round(ans) / 1000.0;
	}

	printf("%.3lf", output);
}
