#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 1260 (DFS와 BFS)
*/
struct cq {
	bool Empty() { return size == 0; }
	int Size() { return size; }
	int Next(int i) { if (++i >= 1001) { i -= 1001; } return i; }
	void PushBack(int i) { cont[end] = i; end = Next(end); ++size; }
	void PopFront() { start = Next(start); --size; }
	int Front() { return cont[start]; }

	int cont[1001]{}, size{}, start{}, end{};
} bfsQ;

#include <bitset>
std::bitset<1001> links[1001], visited;
int N, M, V;

void DFS(int v) {
	visited[v] = true;
	std::cout << v << ' ';

	for (int i = 1; i <= N; ++i) {
		if (links[v][i] && false == visited[i]) {
			DFS(i);
		}
	}
}
void BFS(int v) {
	bfsQ.PushBack(V);
	visited[V] = true;

	while (false == bfsQ.Empty()) {
		int front = bfsQ.Front(); bfsQ.PopFront();
		std::cout << front << ' ';

		for (int i = 1; i <= N; ++i) {
			if (links[front][i] && false == visited[i]) {
				visited[i] = true;
				bfsQ.PushBack(i);
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> M >> V;
	for (int i = 0; i < M; ++i) {
		int a, b; std::cin >> a >> b;
		links[a][b] = true;
		links[b][a] = true;
	}
	DFS(V);
	visited.reset();
	std::cout << '\n';
	BFS(V);

	return 0;
}