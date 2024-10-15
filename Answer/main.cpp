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
#include <memory>
struct node {
	node* parent;
	std::vector<std::unique_ptr<node>> childs;
	int val;
};
std::vector<std::vector<int>> graph;
std::vector<int> dp;	//노드 i의 서브트리 개수가 몇개인지
int N, R, Q;
std::unique_ptr<node> make_tree_recursive(int cur, int parent) {
	std::unique_ptr<node> ret = std::make_unique<node>();
	ret->val = cur;
	
	for (int i = 0; i < (int)graph[cur].size(); ++i) {
		if (graph[cur][i] == parent) { continue; }
		
		//재귀호출
		ret->childs.push_back(make_tree_recursive(graph[cur][i], cur));
		ret->childs.back().get()->parent = ret.get();
	}

	return ret;
}

int count_subtree(node* cur) {
	if (nullptr == cur) { return 0; }

	dp[cur->val] = 1;
	for (const auto& child : cur->childs) {
		dp[cur->val] += count_subtree(child.get());
	}

	return dp[cur->val];
}

void solve() {
	std::cin >> N >> R >> Q;
	graph.resize(N + 1);
	dp.resize(N + 1, -1);
	for (int i = 0; i < N - 1; ++i) {
		int a, b; std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	std::unique_ptr<node> root = make_tree_recursive(R, 0);
	count_subtree(root.get());

	//dp에 저장된 서브트리 출력
	for (int i = 0; i < Q; ++i) {
		int q; std::cin >> q;
		std::cout << dp[q] << '\n';
	}
}