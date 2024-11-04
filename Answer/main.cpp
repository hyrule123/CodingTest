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

#include <cmath>
constexpr double allow_error = 10e-9;

void solve() {
	double X, Y, D, T; cin >> X >> Y >> D >> T;
	double dist_left = sqrt(X * X + Y * Y);

	double sec{}, DpT = D / T;
	
	//혹시나 점프하는게 가성비 구릴지 모르니 확인
	if (1.0 < DpT) {
		//점프 이동거리보다 거리가 멀 경우 일단 원점에서 D 반경 안으로 접근
		int moves = 0;
		if (D <= dist_left) {
			moves = (int)dist_left / (int)D;
		}
		
		dist_left -= (double)moves * D;
		double
			//1. 거리 남기고 걸어오기
			case_1 = (double)moves * T + dist_left,
			//2. 한번 더 가서 돌아오기
			case_2 = (double)(moves + 1) * T + abs(dist_left - D),
			//3. 이등변삼각형 형태로 돌아오기
				//남은 거리가 D * 2 이하이면 점프 두번 해서 오는 길이 반드시 존재한다.
				//이등변삼각형 형태로 돌아서 오는 길이 반드시 존재
				//원점에서 반지름 D인 원을 그리고, 마지막 출발점에서 반지름 D인 원을 그려보면 이해가 쉽다
				//시작점이 범위 이내인 경우 최소 2번 이동해야 하고, 아닐 경우 moves + 1회 이동하면 됨
			case_3 = T * max(2.0, (double)(moves + 1));

		sec += min(case_1, min(case_2, case_3));
	}
	//점프하는게 걸어오는것보다 가성비가 구리다면
	else{
		sec += dist_left;
	}

	printf("%.9lf", sec);
}