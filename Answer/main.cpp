#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1991 (트리 순회)
*/
int n_node;
struct node { char left = '.', right = '.'; };
node tree['Z' + 1];

void pre_order(char idx) {
	std::cout << idx;
	
	if (tree[idx].left != '.') {
		pre_order(tree[idx].left);
	}
	if (tree[idx].right != '.') {
		pre_order(tree[idx].right);
	}
}
void in_order(char idx) {
	if (tree[idx].left != '.') {
		in_order(tree[idx].left);
	}
	std::cout << idx;
	if (tree[idx].right != '.') {
		in_order(tree[idx].right);
	}
}
void post_order(char idx) {
	if (tree[idx].left != '.') {
		post_order(tree[idx].left);
	}
	if (tree[idx].right != '.') {
		post_order(tree[idx].right);
	}
	std::cout << idx;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> n_node;
	for (int i = 0; i < n_node; ++i) {
		char n; std::cin >> n;
		std::cin >> tree[n].left >> tree[n].right;
	}

	pre_order('A');
	std::cout << '\n';
	in_order('A');
	std::cout << '\n';
	post_order('A');
	

	return 0;
}