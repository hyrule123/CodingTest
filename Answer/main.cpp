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
#include <stack>
#include <algorithm>
#define LAND -2
#define NONE -3
int map[100][100], R, C;

struct coord {
	constexpr coord(int _r, int _c) : r(_r), c(_c) { }
	int r, c;

	coord operator + (const coord& other) {
		return { r + other.r, c + other.c };
	}
	void operator +=(const coord& other) {
		r += other.r;
		c += other.c;
	}
	bool valid() {
		return (0 <= r && 0 <= c && r < R && c < C);
	}
};
constexpr coord directions[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct edge {
	int from, to, dist;
	auto operator <(const edge& other) const {
		return dist < other.dist;
	}
	//목적지가 유효한 노드 인덱스이며, 길이가 1 이상이어야 함
	bool valid() {
		return (0 <= to && 1 < dist);
	}
};

struct set_info {
	int group, rank;
};

//start 위치부터 연결된 섬 좌표를 싹 넣어서 반환(하나의 노드 생성)
std::vector<coord> create_node(int node_idx, const coord& start) {
	std::vector<coord> ret;
	std::stack<coord> stk;

	//start부터 시작해서 bfs로 노드 면적 계산
	stk.push(start);
	while (false == stk.empty()) {
		coord cod = stk.top(); stk.pop();
		if (cod.valid() && map[cod.r][cod.c] == LAND) {
			map[cod.r][cod.c] = node_idx;
			ret.push_back(cod);

			//상하좌우 탐색
			for (auto dir : directions) {
				stk.push(cod + dir);
			}
		}
	}
	return ret;
}

std::vector<std::vector<coord>> create_nodes() {
	std::vector<std::vector<coord>> ret;

	//노드 생성
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			if (map[r][c] == LAND) {
				ret.push_back(create_node((int)ret.size(), { r, c }));
			}
		}
	}

	return ret;
}

edge find_edge(coord cod, const coord& dir, int cur_node) {
	edge ret;
	ret.from = cur_node;
	ret.to = NONE;
	ret.dist = 0;

	while (true) {
		cod += dir;
		if (false == cod.valid()) { break; }

		if (map[cod.r][cod.c] == NONE) {
			++ret.dist;
			continue;
		}

		//현재 노드일 경우 (섬을 가로질러 가고있는 경우: 최단거리 불가능)
		if (map[cod.r][cod.c] == cur_node) {
			break;
		}
		//다른 노드일 경우: 도착
		else {
			ret.to = map[cod.r][cod.c];
			break;
		}
	}

	return ret;
}

std::vector<edge> link_possible_edges(const std::vector<std::vector<coord>>& nodes) {
	std::vector<edge> ret;

	for (int i = 0; i < (int)nodes.size(); ++i) {
		for (const auto& cod : nodes[i]) {
			for (auto dir : directions) {
				//지정한 방향으로 쭉 이동하면서 연결될수 있는 노드를 찾는다.
				edge e = find_edge(cod, dir, i);

				//유효한 간선일 경우에만 추가
				if (e.valid()) {
					ret.push_back(e);
				}
			}
		}
	}

	return ret;
}

int find_union(std::vector<set_info>& disjoint_set, int idx) {
	if (disjoint_set[idx].group != idx) {
		disjoint_set[idx].group = find_union(disjoint_set, disjoint_set[idx].group);
	}
	return disjoint_set[idx].group;
}
void make_union(std::vector<set_info>& disjoint_set, int group_a, int group_b) {
	if (disjoint_set[group_a].rank < disjoint_set[group_b].rank) {
		disjoint_set[group_a].group = group_b;
	}
	else {
		disjoint_set[group_b].group = group_a;
	}

	if (disjoint_set[group_a].rank == disjoint_set[group_b].rank) {
		++(disjoint_set[group_a].rank);
	}
}

int Kruskal_MST(std::vector<edge>& edges, int nodes_count) {
	int min_dist = 0;
	int edges_left = nodes_count - 1;

	//union-find 준비
	std::vector<set_info> disjoint_set;
	disjoint_set.resize(nodes_count);
	for (int i = 0; i < nodes_count; ++i) {
		disjoint_set[i].group = i;
		disjoint_set[i].rank = 0;
	}

	//정렬 후 Kruskal 돌린다
	std::sort(edges.begin(), edges.end());
	for (const edge& e : edges) {
		int ga = find_union(disjoint_set, e.from);
		int gb = find_union(disjoint_set, e.to);

		if (ga == gb) { continue; }
		make_union(disjoint_set, ga, gb);

		//거리 추가
		min_dist += e.dist;

		//모든 간선 연결이 완료되면 중단
		--edges_left;
		if (edges_left == 0) { break; }
	}

	//전부 연결하지 못했을 경우 -1을 반환한다.
	if (edges_left != 0) {
		min_dist = -1;
	}
	return min_dist;
}

void solve() {
	std::cin >> R >> C;

	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			std::cin >> map[r][c];
			map[r][c] += NONE;
		}
	}
	std::vector<std::vector<coord>> nodes = create_nodes();
	std::vector<edge> edges = link_possible_edges(nodes);
	std::cout << Kruskal_MST(edges, (int)nodes.size());
}