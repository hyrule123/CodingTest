#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 2667 (단지번호붙이기)
*/
using uint = unsigned int;
//테두리에 0으로 둘러줄예정 + 2, 비트플래그 사용
uint bits[27];
char input[26];
//체스판처럼 101010일 경우 -> 최대 313개가 나옴
uint ans[320], ansIdx = 0;

void DFS(uint r, uint c) {
	if (0u == (1u & bits[r] >> c)) { return; }

	//방문한곳은 플래그를 꺼준다
	bits[r] &= ~(1u << c);
	++(ans[ansIdx]);

	DFS(r - 1, c);
	DFS(r + 1, c);
	DFS(r, c - 1);
	DFS(r, c + 1);
}

uint Partition(uint s, uint e) {
	uint pivot = ans[s];
	uint i = s - 1, j = e + 1;

	while (true) {
		do { ++i; } while (ans[i] < pivot);
		do { --j; } while (ans[j] > pivot);

		if (i >= j) {
			return j;
		}

		std::swap(ans[i], ans[j]);
	}
}

void QuickSort(uint s, uint e) {
	if (s >= e) { return; }

	uint pivot = Partition(s, e);

	QuickSort(s, pivot);
	QuickSort(pivot + 1, e);

}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	uint side; std::cin >> side;
	for (uint i = 1; i <= side; ++i) {
		std::cin >> input;

		//비트플래그 형태로 넣어준다, 역순으로 들어감
		for (uint j = 1; j <= side; ++j) {
			if (input[j - 1] == '1') {
				bits[i] += 1u << j;
			}
		}
	}

	for (uint i = 1; i <= side; ++i) {
		for (uint j = 1; j <= side; ++j) {
			if (1u & bits[i] >> j) {
				DFS(i, j);
				++ansIdx;
			}
		}
	}

	QuickSort(0, ansIdx - 1);
	std::cout << ansIdx << '\n';
	for (uint i = 0; i < ansIdx; ++i) {
		std::cout << ans[i] << '\n';
	}

	return 0;
}