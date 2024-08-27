#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 5639 (이진 검색 트리)
*/
/*
* 전위 순회한 결과가 주어진다 -> 루트부터 시작해서 왼쪽, 오른쪽 순서로
*/
constexpr int MAX = 10001;
int n_node, pre_order[MAX];

void insert_btree(int pre_start, int pre_end) {
	if (pre_start > pre_end) { return; }

	//역순으로 순회를 돌아주면서현재 루트노드보다 최초로 작은 값이 나오는 지점을 기록한다.
	//루트노드 왼쪽은 무조건 루트노드보다 작은 값들만 모여있고
	// 오른쪽은 무조건 루트노드보다 큰 값들만 모여있다
	//이 분기점을 기준으로 왼쪽, 오른쪽 나눠서 DFS 호출
	int div_part = pre_end;
	for (int i = pre_end; i >= pre_start + 1; --i) {
		if (pre_order[i] < pre_order[pre_start]) {
			div_part = i;
			break;
		}
	}

	//좌측
	insert_btree(pre_start + 1, div_part);

	//우측
	insert_btree(div_part + 1, pre_end);

	//포스트오더이므로 자신에 대한 출력은 제일 마지막에
	std::cout << pre_order[pre_start] << '\n';
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int idx = 0;
	while (std::cin >> pre_order[++idx]) { ++n_node; }

	insert_btree(1, n_node);
	return 0;
}