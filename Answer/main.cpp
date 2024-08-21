#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 2618 (경찰차)
*/
//memo[i][j] 1번이 i위치, 2번이 j위치에 있을 때 max(i, j) + 1 ~ case_n번 사건을 해결하는 데 필요한 최소 거리

constexpr int MAX = 1024;
int map_size, case_n, memo[MAX][MAX];	
struct coord { int x, y; };
coord case_pos[MAX];

inline int ABS(int i) { if (i < 0) { i = -i; } return i; }
inline int dist(const coord& a, const coord& b) {
	return ABS(b.x - a.x) + ABS(b.y - a.y);
}

int nearest_dist(int last_1, int last_2) {
	//두 경찰차가 해결한 마지막 사건 + 1이 다음 사건 번호
	int next = std::max(last_1, last_2) + 1;
	if (next == case_n) { return 0; }
	else if (memo[last_1][last_2] != -1) { return memo[last_1][last_2]; }

	//각각 경찰차가 next로 이동할 때의 거리를 구한다.
	int dist1 = dist(case_pos[last_1], case_pos[next]);
	int dist2 = dist(case_pos[last_2], case_pos[next]);
	
	//다음으로 두 경찰차의 목적지에 대한 DFS 시행
	//1번 경찰차가 next로 이동한 경우
	int total_dist1 = dist1 + nearest_dist(next, last_2);
	int total_dist2 = dist2 + nearest_dist(last_1, next);

	memo[last_1][last_2] = std::min(total_dist1, total_dist2);
	return memo[last_1][last_2];
}

void trace_back(int last_1, int last_2) {
	int next = std::max(last_1, last_2) + 1;
	if (next == case_n) { return; }

	int dist1 = dist(case_pos[last_1], case_pos[next]);
	int dist2 = dist(case_pos[last_2], case_pos[next]);

	if (dist1 + memo[next][last_2] < dist2 + memo[last_1][next]) {
		std::cout << 1 << '\n';
		trace_back(next, last_2);
	}
	else {
		std::cout << 2 << '\n';
		trace_back(last_1, next);
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	memset(memo, -1, sizeof(memo));

	std::cin >> map_size >> case_n;
	
	//0번 1번 항목에는 경찰차의 첫 시작 위치를 저장, 2번부터 실제 input
	case_n += 2;
	case_pos[0] = { 1, 1 };
	case_pos[1] = { map_size, map_size };

	for (int i = 2; i < case_n; ++i) {
		std::cin >> case_pos[i].x >> case_pos[i].y;
	}

	std::cout << nearest_dist(0, 1) << '\n';
	trace_back(0, 1);

	return 0;
}