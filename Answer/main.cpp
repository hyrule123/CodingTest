#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif

#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////
#include <vector>
struct colorCount { 
	int white, blue; 
	void operator +=(const colorCount& _other) {
		white += _other.white;
		blue += _other.blue;
	}
};
std::vector<std::vector<bool>> paper;
colorCount Recursive(int _r, int _c, int _size) {
	colorCount ret{};

	for (int r = _r; r < _r + _size; ++r) {
		for (int c = _c; c < _c + _size; ++c) {
			if (paper[r][c]) {
				++ret.blue;
			}
			else {
				++ret.white;
			}
		}
	}
	//하나로만 이루어져있다면 있는 쪽을 1로 바꾼 뒤 return
	if (ret.white == 0 || ret.blue == 0) {
		ret.white = !!ret.white;
		ret.blue = !!ret.blue;
		return ret;
	}

	int half = _size / 2;
	ret = Recursive(_r, _c,half);
	ret += Recursive(_r + half, _c,	half);
	ret += Recursive(_r, _c + half,	half);
	ret += Recursive(_r + half, _c + half, half);

	return ret;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	int N; std::cin >> N;
	paper.resize(N, std::vector<bool>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int input; std::cin >> input;
			if (input) { paper[i][j] = true; }
		}
	}
	colorCount ans = Recursive(0, 0, N);
	std::cout << ans.white << '\n' << ans.blue;

	return 0;
}
