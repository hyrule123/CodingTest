#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 24479, 24480 (알고리즘 수업 - 깊이 우선 탐색 1, 2) - 부등호 방향만 달라져서 그냥 같이 올림
*/
#include <bitset>
#include <vector>
std::vector<int> links[100001];
std::vector<int> temp;
std::bitset<100001> visits{};
int ans[100001]{}, visitOrder = 1;
int N, M, R, size = 0;

void MergeSort(std::vector<int>& _vec, int _start, int _end) {
	if (_start >= _end) { return; }

	int mid = (_start + _end) / 2;
	MergeSort(_vec, _start, mid);
	MergeSort(_vec, mid + 1, _end);

	int cursor = 0;
	int left = _start;
	int right = mid + 1;
	while (left <= mid && right <= _end) {
		if (_vec[left] > _vec[right]) {
			temp[cursor++] = _vec[left++];
		}
		else {
			temp[cursor++] = _vec[right++];
		}
	}
	for (; left <= mid;) {
		temp[cursor++] = _vec[left++];
	}
	for (; right <= _end;) {
		temp[cursor++] = _vec[right++];
	}

	memcpy(_vec.data() + _start, temp.data(), sizeof(int) * (_end - _start + 1));
}

void DFS(int _node) {
	if (false == visits[_node]) {
		visits[_node] = true;
		ans[_node] = visitOrder;
		++visitOrder;
	}

	for (int i : links[_node]) {
		if (false == visits[i]) { DFS(i); }
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> M >> R;
	for (int i = 0; i < M; ++i) {
		int from, to; std::cin >> from >> to;
		links[from].push_back(to);
		links[to].push_back(from);
	}
	for (int i = 1; i <= N; ++i) {
		temp.resize(links[i].size());
		MergeSort(links[i], 0, (int)links[i].size() - 1);
	}
	DFS(R);
	for (int i = 1; i <= N; ++i) {
		std::cout << ans[i] << '\n';
	}
	return 0;
}