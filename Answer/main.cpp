#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 4803 (트리)
*/
/*
* 전위 순회한 결과가 주어진다 -> 루트부터 시작해서 왼쪽, 오른쪽 순서로
*/
#include <vector>
#include <bitset>

template <typename T>
struct cq {
	bool empty() { return size == 0; }
	bool full() { return cap == size; }
	void reserve(int c) {
		if (c <= cap) { return; }

		T* temp = new T[c];
		if (cont) {
			if (false == empty()) {
				if (start < end) {
					memcpy(temp, cont + start, sizeof(T) * size);
				}
				else {
					int start_part_size = cap - start;
					memcpy(temp, cont + start, sizeof(T) * start_part_size);
					memcpy(temp + start_part_size, cont, sizeof(T) * end);
				}
			}

			delete[] cont;
		}

		cont = temp;
		cap = c;
		start = 0;
		end = size;
	}
	int next(int i) { if (++i >= cap) { i -= cap; } return i; }
	void push(const T& _t) { 
		if (full()) { reserve(cap * 2); }
		cont[end] = _t;
		end = next(end);
		++size;
	}
	T pop() {
		T ret = cont[start];
		start = next(start);
		--size;
		return ret;
	}
	void clear() { start = end = size = 0; }

	T* cont{};
	int cap{}, size{}, start{}, end{};
};

constexpr int MAX = 501;
int case_num, n_node, n_edge;
std::vector<int> graph[MAX];
std::bitset<MAX> visited;
cq<int> q;
void reset() {
	n_node = 0;
	n_edge = 0;
	for (int i = 0; i < MAX; ++i) {
		graph[i].clear();
	}
	visited.reset();
	q.clear();
	q.reserve(512);
}

bool is_tree_BFS(int node) {
	q.push(node);

	bool ret = true;
	while (false == q.empty()) {
		int cur = q.pop();

		//이번 노드를 방문처리하기 전에 이미 방문한 노드인지 확인해본다.
		//혹시나 이미 방문돼있는 노드일 경우 회로가 존재하는 것.
		if (visited[cur]) {
			ret = false;
		}
		
		//방문처리
		visited[cur] = true;

		//방문처리 안 된 노드에 대해 큐에 삽입.
		for (int next : graph[cur]) {
			if (false == visited[next]) {
				q.push(next);
			}
		}
	}

	return ret;
}

void print_ans(int cur_case, int n_tree) {
	std::cout << "Case " << cur_case << ": ";

	if (n_tree == 0) {
		std::cout << "No trees.";
	}
	else if (n_tree == 1) {
		std::cout << "There is one tree.";
	}
	else {
		std::cout << "A forest of " << n_tree << " trees.";
	}

	std::cout << '\n';
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int case_num = 0;
	while(true){
		reset();
		++case_num;

		std::cin >> n_node >> n_edge;
		if (n_node == 0 && n_edge == 0) {
			break;
		}

		for (int e = 1; e <= n_edge; ++e) {
			int a, b; std::cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		//단일 노드로 구성된 그래프도 '트리'라고 부를 수 있다.
		/*
		* 예제 입력의 첫번째 케이스는 노드가 6개인데 4번 노드까지만 회로가 없는 연결이 있다.
		* 5, 6번 노드는 아무 노드와도 연결되어있지 않은 단일 노드이다.
		* -> 트리 3개
		*/
		int n_tree = 0;
		for (int n = 1; n <= n_node; ++n) {
			if (false == visited[n]) {
				if (is_tree_BFS(n)) { ++n_tree; }
			}
		}

		print_ans(case_num, n_tree);
	}

	return 0;
}