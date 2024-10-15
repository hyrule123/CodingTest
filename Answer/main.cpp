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
#include <queue>
#include <algorithm>
#define NODE_START 2

struct edge {
	int from, to, dist;

	//for priority queue
	auto operator < (const edge& other) const {
		return this->dist > other.dist;
	}
};

int R, C;

struct coord {
	constexpr coord(int _r, int _c) : r(_r), c(_c) { }
	int r, c;
	void operator += (const coord& cod) {
		r += cod.r;
		c += cod.c;
	}
	coord operator + (const coord& cod) {
		return { this->r + cod.r, this->c + cod.c };
	}
	bool valid() {
		return (0 <= r && 0 <= c && r < R && c < C);
	}
};

constexpr coord directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
std::vector<std::vector<int>> map;
std::vector<std::vector<coord>> nodes;
std::priority_queue<edge> pq;

void make_nodes(int r, int c, int node_num) {
	std::stack<coord> dfs;
	dfs.push({ r, c });
	if ((int)nodes.size() <= node_num)
	{
		nodes.resize(node_num + 1);
	}

	while (false == dfs.empty()) {
		coord cod = dfs.top(); dfs.pop();

		if (cod.valid() && map[cod.r][cod.c] == 1) {
			map[cod.r][cod.c] = node_num;

			//edge 만들때 쓰기 위한 nodes
			nodes[node_num].push_back(cod);

			for (auto dir : directions) {
				dfs.push(cod + dir);
			}
		}
	}
}

void create_graph() {
	//0이랑 1은 쓰고있으니까 NODE_START(2)부터 시작
	int node_num = NODE_START;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			if (1 == map[r][c]) {
				make_nodes(r, c, node_num);
				++node_num;
			}
		}
	}
}

edge make_path(coord cur_cod, const coord& dir, int cur_node_num) {
	edge ret{};
	ret.from = cur_node_num;

	while (true) {
		cur_cod += dir;

		if (false == cur_cod.valid()) { break; }

		//0(바다)일 시 계속 나아간다
		if (map[cur_cod.r][cur_cod.c] == 0) {
			ret.dist += 1;
			continue;
		}

		//자신과 같은 노드번호가 있을경우 break(섬을 가로질러서 가고있는것->최단거리가 될수없음)
		if (map[cur_cod.r][cur_cod.c] == cur_node_num) {
			break;
		}
		//0이 아니면서 현재 노드 번호도 아니면 새 노드와 연결된 것
		else {
			ret.to = map[cur_cod.r][cur_cod.c];
			break;
		}
	}

	return ret;
}

void insert_edges(int node_num) {
	if (node_num >= nodes.size()) { return; }
	
	for (const coord& c : nodes[node_num]) {
		for (auto dir : directions) {
			edge e = make_path(c, dir, node_num);

			//연결되면서 거리가 1 이상일 경우에만 간선이 될 수 있다
			if (e.to != 0 && e.dist > 1) { pq.push(e); }
		}
	}
}

int Prim_MST() {
	int total_dist = 0;

	int edge_count = (int)nodes.size() - NODE_START - 1;

	std::vector<bool> visited(nodes.size());
	visited[NODE_START] = true;

	insert_edges(NODE_START);
	while (false == pq.empty() && 0 < edge_count) {
		edge e = pq.top(); pq.pop();

		if (visited[e.to]) { continue; }

		visited[e.to] = true;
		
		--edge_count;
		total_dist += e.dist;
		insert_edges(e.to);
	}

	//길이 전부 놓여지지 않았을 경우 -1을 출력한다.
	if (edge_count != 0) {
		total_dist = -1;
	}
	return total_dist;
}

void solve()
{
	std::cin >> R >> C;
	map.resize(R, std::vector<int>(C));

	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			std::cin >> map[r][c];
		}
	}
	create_graph();
	std::cout << Prim_MST();
}
