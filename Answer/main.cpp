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
백준 26523 (균등분포와 정규분포) [확률과 통계][오답]
입력 데이터는 
U(0, 1) 균등분포의 0,1 구간에서 추출된 데이터 5000개
또는
N(0.5, 0.1) 정규분포의 0, 1 구간에서 추출된 데이터 5000개

전자의 경우 넓이가 1에 근접할 것이고
후자의 경우 넓이가 정규분포를 적분한 값에 근접할 것이다

우선 정규분포의 0.25 ~ 0.75 확률 / 0~.25 + .75~1 확률의 비율을 구한다
균등분포는 각각 구간이 동일하므로 0.5 / 0.5 = 1의 비율일 것이다

입력된 데이터도 동일한 구간으로 나눠서 비율을 구한다

둘 중 가까운 쪽을 답으로 선정한다.
*/
#include <cmath>
#include <numbers>
int TC = 100;
constexpr double mean = 0.5, distrib = 0.1, precision = 0.0001, n = 5000;
double integ_norm(double from, double to) {
	static double coef = 1.0 / (sqrt(2 * numbers::pi * distrib));

	double result = 0;
	for (double x = from; x <= to + numeric_limits<double>::epsilon(); x += precision) {
		double _exp = -(pow(x - mean, 2.0) / (2 * distrib));
		_exp = exp(_exp);
		result += coef * _exp * precision;
	}
	
	return result;
}

int _25_to_75_count, other_count; //0~0.25, 0.75~1

void solve() {
	//0~1 사이가 나올 확률
	double norm_0_to_1 = integ_norm(0.0, 1.0);
	//.25~.75 사이가 나올 확률
	double norm_25_to_75 = integ_norm(0.25, 0.75);

	//0 ~ .25, .75~1 구간이 나올 확률
	double other = norm_0_to_1 - norm_25_to_75;

	//.25 ~.75 나올 확률 / 나머지 구간 확률의 비율을 구한다
	double norm_ratio = norm_25_to_75 / other;

	while (TC--) {
		//입력도 마찬가지로 위와 같은 구간으로 구분하고, 비율을 구한다
		for (int i = 0; i < n; ++i) {
			double input; cin >> input;
			if (0.25 <= input && input <= 0.75) {
				++_25_to_75_count;
			}
			else {
				++other_count;
			}
		}

		double input_ratio = (double)_25_to_75_count / (double)other_count;

		//정규분포 비율과의 차이, 균등분포 비율과의 차이를 구한다
		double norm_dist = abs(norm_ratio - input_ratio);

		//마찬가지로 균등분포도 차이를 구한다.
		//균등분포는 전 구간 출현 확률이 같으므로
		//.25~.75 구간(0.5) / 0~.25 + .75~1 구간(0.5)를 해주면 1이 나온다
		double uniform_dist = abs(1.0 - input_ratio);

		//둘중 가까운 쪽을 답으로 선정
		if (uniform_dist < norm_dist) {
			cout << "A\n";
		}
		else {
			cout << "B\n";
		}
	}
}