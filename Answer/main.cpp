#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 2263 (트리의 순회)
*/
constexpr int MAX = 100001;
int n_node, inorder[MAX], postorder[MAX], idx_of_inorder[MAX];

//포스트오더 + 인오더를 결합하면 
//포스트오더에서 부모 노드를 찾을 수 있고
//인오더에서는 부모노드를 기준으로 좌우로 분할이 가능하다.
//분할된 포스트오더/인오더에서도 똑같이 작동하므로 DFS 재귀호출로 풀이가 가능
/*
* inorder 1 2 3
* postorder 1 3 2
*/
void convert_preorder(int in_start, int in_end, int post_start, int post_end) {
	if (in_start > in_end) { return; }
	else if (post_start > post_end) { return; }

	//postorder의 우측 끝 값이 inorder에서 어디 있는지 찾는다.
	//depth 1: root = 2, root_idx = 2(2가 inorder 배열의 2번째 위치에 있다)
	int root_idx = idx_of_inorder[postorder[post_end]];
	int left_part_size = root_idx - in_start;

	//위 위치를 기준으로 좌/우를 분해하여 재귀호출을 한다
	//프리오더는 루트->좌->우 이므로 루트부터 출력한다.
	std::cout << postorder[post_end] << ' ';

	/*
	inorder 2를 기준으로 좌우 분할한다. (n): 제외되는 부분
	inorder: 1 (2) 3
	postorder: 1 / 2 (3)
	*/

	//in: 1~1, post: 1~1
	convert_preorder(in_start, root_idx - 1, post_start, post_start + left_part_size - 1);

	//in: 3~3, post: 2~2
	convert_preorder(root_idx + 1, in_end, post_start + left_part_size, post_end - 1);
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> n_node;
	for (int i = 1; i <= n_node; ++i) {
		std::cin >> inorder[i];

		//inorder[i]의 수가 몇 번째 인덱스에 들어있는지도 저장해둔다(데이터 탐색 용도)
		idx_of_inorder[inorder[i]] = i;
	}
	for (int i = 1; i <= n_node; ++i) {
		std::cin >> postorder[i];
	}
	convert_preorder(1, n_node, 1, n_node);

	return 0;
}