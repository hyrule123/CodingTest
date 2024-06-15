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
std::vector<std::vector<char>> screen;
void RecursivePrint(int _r, int _c, int _size) {
	char first = screen[_r][_c];

	bool diff = false;
	for (int r = _r; r < _r + _size; ++r) {
		for (int c = _c; c < _c + _size; ++c) {
			if (first != screen[r][c]) {
				std::cout << '(';

				int half = _size / 2;
				RecursivePrint(_r, _c, half);
				RecursivePrint(_r, _c + half, half);
				RecursivePrint(_r + half, _c, half);
				RecursivePrint(_r + half, _c + half, half);

				std::cout << ')';
				return;
			}
		}
	}

	std::cout << first;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	int N; std::cin >> N;
	(void)std::cin.get();
	screen.resize(N, std::vector<char>(N + 1));
	for (int i = 0; i < N; ++i) {
		std::cin.getline(screen[i].data(), N + 1);
	}
	RecursivePrint(0, 0, N);

	return 0;
}
