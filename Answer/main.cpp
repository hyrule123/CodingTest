#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
struct paperCount { 
	int p[3];
	void operator += (const paperCount& _other) {
		p[0] += _other.p[0];
		p[1] += _other.p[1];
		p[2] += _other.p[2];
	}
};
std::vector<std::vector<int>> paper;
paperCount Recursive(int _size, int _r, int _c) {
	paperCount ret{};
	//이거 안하는게 더 빠름(했을 때 384 -> 안했을 때 348)
	//if (_size == 1) { ret.p[paper[_r][_c]] = 1; return ret; }

	int first = paper[_r][_c];
	for (int r = _r; r < _r + _size; ++r) {
		for (int c = _c; c < _c + _size; ++c) {

			//하나라도 다를 경우
			if (first != paper[r][c]) {
				int oneThird = _size / 3;
				for (int i = 0; i < _size; i += oneThird) {
					for (int j = 0; j < _size; j += oneThird) {
						ret += Recursive(oneThird, _r + i, _c + j);
					}
				}
				return ret;
			}
		}
	}

	//모두 같을 경우
	ret.p[first] = 1;
	return ret;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	int N; std::cin >> N;
	paper.resize(N, std::vector<int>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> paper[i][j];
			//-1 0 1을 인덱스로 사용하기 위해서 +1
			++(paper[i][j]);
		}
	}

	paperCount counts = Recursive(N, 0, 0);
	std::cout << counts.p[0] << '\n' << counts.p[1] << '\n' << counts.p[2];

	return 0;
}
