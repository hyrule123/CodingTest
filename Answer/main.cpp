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

#include <vector>
#include <algorithm>
struct vec2 {
	double x, y;

	auto operator <=> (const vec2& other) const {
		if (x == other.x) {
			return y <=> other.y;
		}
		return x <=> other.x;
	}

	auto operator == (const vec2& other) const {
		return x == other.x && y == other.y;
	}
	auto operator != (const vec2& other) const {
		return !(*this == other);
	}
	double cross(const vec2& other) const {
		return x * other.y - other.x * y;
	}
	vec2 operator - (const vec2& other) const {
		return { x - other.x, y - other.y };
	}

	static double ccw(const vec2& from, const vec2& std, const vec2& a, const vec2& b) {
		vec2 standard = std - from;
		return (standard.cross(a - from) * standard.cross(b - from));
	}
};

struct line_seg {
	int group, rank = 0, size = 1;
	vec2 p[2];
};

//v1 실패 원인: biggest_group_size를 0으로 잡았음
int N, num_group, biggest_group_size = 1;
vector<line_seg> lines;

int find_group(int node) {
	if (lines[node].group != node) {
		lines[node].group = find_group(lines[node].group);
	}
	return lines[node].group;
}
void union_group(int na, int nb) {
	int pa = find_group(na);
	int pb = find_group(nb);

	if (pa == pb) { return; }

	//union이 발생했으므로 집합 개수 1개 감소
	//v1 실패 원인: pa, pb를 사용한것이 아니라 na, nb를 사용
	--num_group;
	if (lines[pa].rank < lines[pb].rank) {
		lines[pa].group = pb;

		//사이즈 병합
		lines[pb].size += lines[pa].size;
		biggest_group_size = max(biggest_group_size, lines[pb].size);
	}
	else {
		lines[pb].group = pa;
		lines[pa].size += lines[pb].size;
		biggest_group_size = max(biggest_group_size, lines[pa].size);
	}

	if (lines[pa].rank == lines[pb].rank) {
		++(lines[pa].rank);
	}
}

void solve() {
	cin >> N;
	num_group = N;
	lines.resize(N);
	for (int i = 0; i < N; ++i) {
		line_seg& l = lines[i];
		cin >> l.p[0].x >> l.p[0].y >> l.p[1].x >> l.p[1].y;
		if (l.p[0] > l.p[1]) {
			swap(l.p[0], l.p[1]);
		}
		l.group = i;
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			line_seg& l = lines[i], & r = lines[j];
			
			double
				ccw1 = vec2::ccw(l.p[0], l.p[1], r.p[0], r.p[1]),
				ccw2 = vec2::ccw(r.p[0], r.p[1], l.p[0], l.p[1]);

			//같은 직선 위의 점
			if (ccw1 == 0.0 && ccw2 == 0.0) {
				bool no_intersect1 = l.p[0] > r.p[1];
				bool no_intersect2 = r.p[0] > l.p[1];

				//둘이 교차한다 -> 그룹 통일
				if (!(no_intersect1 || no_intersect2)) {
					union_group(i, j);
				}
			}
			//서로 한 점에서 교차 -> 그룹 통일
			else if (ccw1 <= 0.0 && ccw2 <= 0.0) {
				union_group(i, j);
			}
		}
	}

	cout << num_group << '\n' << biggest_group_size;
}
