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

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
std::array<int, 8> order = { 0, 1, 2, 3, 4, 5, 6, 7 };
float stats[8];



struct vec {
	float x, y;
	void operator -= (const vec& other) {
		x -= other.x;
		y -= other.y;
	}
	float cross(const vec& other) {
		return (x * other.y - other.x * y);
	}
};

/*
* left->right 벡터에서 left->mid 벡터를 외적했을때
|\
| \ * <- mid가 여깄으면 반시계 방향이므로 양수: 볼록
|* \ <- mid가 여깄으면 시계 방향이므로: 오목
|   \
---------
*/
//1사분면에다 놓고 테스트할 예정, 시계방향 순서대로 입력
bool is_bolock(float left, float mid, float right) {
	//cos 45 == sin 45
	constexpr float cos45 = 0.70710678118f;

	//설명: left 좌표를 기준으로
	const vec l = { 0, left };
	vec left_to_right = { right, 0 };
	vec left_to_mid = { mid * cos45, mid * cos45 };

	//상대벡터 2개를 생성한다.
	left_to_right -= l;
	left_to_mid -= l;

	//외적값이 양수면 볼록 삼각형이다.
	return 0.0f <= left_to_right.cross(left_to_mid);
}

bool test_case() {
	for (int i = 0; i < 8; ++i) {
		float left = stats[order[i]];
		float mid = stats[order[(i + 1) % 8]];
		float right = stats[order[(i+ 2) % 8]];

		//하나라도 오목일경우 false
		if (false == is_bolock(left, mid, right)) {
			return false;
		}
	}

	return true;
}

void solve() {
	for (float& s : stats) {
		std::cin >> s;
	}

	int ans = 0;
	//
	do {
		if (test_case()) {
			++ans;
		}
	}
	//아래 코드는 매번 순열 조합에 따라서 숫자를 배열한다.
	while (std::next_permutation(order.begin(), order.end()));

	std::cout << ans;
}