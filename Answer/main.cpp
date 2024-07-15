#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 2606 (바이러스)
*/
#include <bitset>
std::bitset<101> links[101], visited;
int nNode, nLink, infectedCount = -1;
void DFS(int node) {
	visited[node] = true;
	++infectedCount;

	for (int i = 1; i <= nNode; ++i) {
		if (links[node][i] && false == visited[i]) {
			DFS(i);
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> nNode >> nLink;
	for (int i = 0; i < nLink; ++i) {
		int a, b; std::cin >> a >> b;
		links[a][b] = true;
		links[b][a] = true;
	}
	DFS(1);
	std::cout << infectedCount;

	return 0;
}